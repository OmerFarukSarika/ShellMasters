#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#define HISTORY_FILE ".custom_history"
void load_history() {
    char* home = getenv("HOME");
    if (!home) return;
    char history_path[1024];
    snprintf(history_path, sizeof(history_path), "%s/%s", home, HISTORY_FILE);
    read_history(history_path);
}
void save_history() {
    char* home = getenv("HOME");
    if (!home) return;
    char history_path[1024];
    snprintf(history_path, sizeof(history_path), "%s/%s", home, HISTORY_FILE);
    write_history(history_path);
}
char* rl_custom_function(const char* prompt) {
    char* line = readline(prompt);
    if (line && *line) {
        add_history(line);
        save_history();  // Her giriş sonrası geçmişi kaydet
    }
    return line;
}
int main() {
    char* line;
    // Readline'ı başlat
    //rl_bind_key('\t', rl_insert);
    // Geçmişi yükle
    load_history();
    while ((line = rl_custom_function("Komut: ")) != NULL) {
        if (strcmp(line, "exit") == 0) {
            free(line);
            break;
        }
        if (strcmp(line, "") == 0) {
            printf("Yukarı ok: Önceki komut\n");
            printf("Aşağı ok: Sonraki komut\n");
        } else {
            printf("Girilen komut: %s\n", line);
        }
        free(line);
    }
    printf("Program sonlandı.\n");
    save_history();  // Program sonunda geçmişi son kez kaydet
    return 0;
}