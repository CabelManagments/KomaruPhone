#include "komaru_display.h"
#include "komaru_buttons.h"
#include "komaru_wifi.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>

#define MAX_URL 256
#define MAX_HTML 16384

static char current_url[MAX_URL] = "http://komaru.phone";
static char page_text[MAX_HTML];
static int link_positions[100][2]; // [y_start, y_end] для кликов
static int link_count = 0;

int http_get(const char *host, const char *path, char *response, int max_len) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct hostent *server = gethostbyname(host);
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    memcpy(&addr.sin_addr.s_addr, server->h_addr, server->h_length);
    addr.sin_port = htons(80);
    
    if(connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) return -1;
    
    char request[512];
    snprintf(request, sizeof(request),
             "GET %s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n",
             path, host);
    send(sock, request, strlen(request), 0);
    
    int total = 0;
    int bytes;
    while((bytes = recv(sock, response + total, max_len - total - 1, 0)) > 0) {
        total += bytes;
    }
    response[total] = '\0';
    close(sock);
    return total;
}

void parse_html(char *html, char *output) {
    // Вырезаем текст и запоминаем ссылки
    int in_tag = 0;
    int out_pos = 0;
    int in_link = 0;
    char link_href[256] = "";
    int link_href_pos = 0;
    
    for(int i = 0; html[i] && out_pos < MAX_HTML-1; i++) {
        if(html[i] == '<') {
            in_tag = 1;
            // проверка на <a href="...">
            if(strncmp(html+i, "<a href", 7) == 0) {
                in_link = 1;
                link_href_pos = 0;
                memset(link_href, 0, sizeof(link_href));
                char *start = strchr(html+i, '"');
                if(start) {
                    start++;
                    char *end = strchr(start, '"');
                    if(end) {
                        int len = end - start;
                        strncpy(link_href, start, len);
                        link_href[len] = '\0';
                    }
                }
            }
            continue;
        }
        if(html[i] == '>') {
            in_tag = 0;
            // конец ссылки
            if(in_link) {
                // запоминаем позицию текста ссылки
                link_positions[link_count][0] = out_pos;
                in_link = 0;
            }
            continue;
        }
        if(!in_tag) {
            output[out_pos++] = html[i];
            if(in_link && html[i] == '<') {
                // конец текста ссылки
                link_positions[link_count][1] = out_pos - 1;
                link_count++;
            }
        }
    }
    output[out_pos] = '\0';
}

void browser_draw_text(const char *text, int *scroll) {
    komaru_display_clear();
    int y = 10 - *scroll;
    const char *line_start = text;
    
    for(int i = 0; text[i]; i++) {
        if(text[i] == '\n' || (i > 0 && (i % 30 == 0))) {
            char line[64];
            int len = (text + i) - line_start;
            strncpy(line, line_start, len);
            line[len] = '\0';
            komaru_display_string(line, 5, y);
            y += 12;
            if(y > 120) break;
            line_start = text + i + 1;
        }
    }
}

void komaru_browser_run(void) {
    char html[MAX_HTML];
    int scroll = 0;
    int running = 1;
    
    // Загружаем стартовую страницу
    if(http_get("komaru.phone", "/", html, MAX_HTML) > 0) {
        parse_html(html, page_text);
    } else {
        strcpy(page_text, "Нет соединения\nKomaruBrowser\nНажмите Vol+ для обновления");
    }
    
    while(running) {
        browser_draw_text(page_text, &scroll);
        komaru_display_string(current_url, 5, 120);
        
        int btn = komaru_buttons_read();
        if(btn & BTN_VOLUME_UP) {
            scroll += 10;
        }
        if(btn & BTN_VOLUME_DOWN) {
            scroll -= 10;
            if(scroll < 0) scroll = 0;
        }
        if(btn & BTN_POWER) {
            running = 0;
        }
        
        komaru_display_update();
        usleep(100000);
    }
}
