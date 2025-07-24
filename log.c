#include "log.h"
#include "ansi.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

static FILE* logFile = NULL;

const char* horaAtualFormatada() {
    static char horas[11];
    time_t agora = time(NULL);
    struct tm* t = localtime(&agora);
    snprintf(horas, sizeof(horas), "[%02d:%02d:%02d]", t->tm_hour, t->tm_min, t->tm_sec);
    return horas;
}

void logInfo(const char* mensagem) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "[INFO] %s", mensagem);
    logToFile(buffer);

    printf("%s "TEXTO_VERDE        "[INFO] "RESET           "%s\n",  horaAtualFormatada() ,mensagem);

}

void logWarn(const char* mensagem) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "[WARN] %s", mensagem);
    logToFile(buffer);

    printf("%s " TEXTO_AMARELO      "[WARN] " RESET          "%s\n", horaAtualFormatada(), mensagem);
}

void logError(const char* mensagem) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "[ERROR] %s", mensagem);
    logToFile(buffer);

    printf("%s " TEXTO_VERMELHO     "[ERROR] "RESET          "%s\n", horaAtualFormatada(), mensagem);
}

void initLog() {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    char filename[64];
    // Formato: log_AAAAmmdd_HHMMSS.txt
    strftime(filename, sizeof(filename), "log_%Y%m%d_%H%M%S.txt", t);

    logFile = fopen(filename, "a");
    if (logFile == NULL) {
        perror("Erro ao criar arquivo de log");
        exit(1);
    }
    fprintf(logFile, "%s %s\n", horaAtualFormatada(), "JOGO INICIADO\n");
}

void logToFile(const char* mensagem) {
    if (logFile == NULL) {
        initLog();
    }
    fprintf(logFile, "%s %s\n", horaAtualFormatada(), mensagem);
    fflush(logFile);
}

void closeLog() {
    if (logFile != NULL) {
        fclose(logFile);
        logFile = NULL;
    }
}

void logMovimento(int xAnt, int yAnt, int xPos, int yPos){
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "[INFO] O jogador se mexeu da posicao [%d][%d] para a posicao [%d][%d]", yAnt, xAnt, yPos, xPos);
    logToFile(buffer);
}