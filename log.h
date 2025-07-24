const char* horaAtualFormatada();

void                logInfo                 (const char*); // Função para mostrar informações e coloca-la em um arquivo log
void                logWarn                 (const char*); // Função para mostrar avisos e coloca-lo em um arquivo log
void                logError                (const char*); // Função para mostrar erros e coloca-lo em um arquivo log
void                logToFile               (const char*); // Função que coloca um texto diretamente num arquivo log
void                logMovimento            (int, int, int, int); // Função que coloca o movimento do player no mapa no arquivo log

void                initLog                 (); // Função para iniciar o log
void                closeLog                (); // Função que fecha o log


