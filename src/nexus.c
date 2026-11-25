/*
 * ============================================================================
 *  NEXUS - Jogo educativo de aventura e exploracao no terminal
 *  Projeto Integrador - CESAR School
 *  Versao parcial (parte 1): Menu + instrucoes + mapas e movimentacao
 *  Plataforma: Windows (terminal integrado do VS Code)
 * ============================================================================
 *
 *  Organizacao do game loop (laco principal, repetido ate o jogador sair):
 *    (A) reinicia o jogo, se pedido
 *    (B) desenha a tela atual
 *    (C) le e valida a tecla (sem precisar apertar ENTER)
 *    (D) processa a tecla e decide qual sera a proxima tela
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>   /* system("cls"): limpa a tela do terminal do Windows */
#include <conio.h>    /* _getch(): le uma tecla na hora, sem precisar de ENTER */

/* ----------------------------------------------------------------------------
 * LEITURA DE TECLAS (Windows)
 * Com scanf/getchar, o terminal so entrega o que foi digitado depois do
 * ENTER. A funcao _getch(), da biblioteca conio.h, le a tecla assim que ela
 * e apertada e nao a mostra na tela.
 * Setas e teclas F1..F12 enviam DOIS codigos: primeiro 0 ou 224, depois o
 * codigo da tecla. O jogo descarta esses dois codigos.
 * -------------------------------------------------------------------------- */
#define TECLA_ESPECIAL_1  0
#define TECLA_ESPECIAL_2  224

/* ----------------------------------------------------------------------------
 * TELAS DO JOGO
 * O jogo e uma "maquina de estados": telaAtual guarda em qual tela o jogador
 * esta. Cada tela tem um numero (constante) diferente.
 * -------------------------------------------------------------------------- */
#define TELA_MENU              0   /* menu inicial (US01)                     */
#define TELA_INSTRUCOES        1   /* lista de comandos (US02)                */
#define TELA_MAPA              2   /* exploracao do mapa (US03 e US04)        */
#define TELA_PISTA             3   /* Fase 1: leitura da pista (US05)         */
#define TELA_COMPUTADOR1       4   /* Fase 1: afirmacoes da IA (US06)         */
#define TELA_COMPUTADOR2       5   /* Fase 1: filtro de confianca (US07)      */
#define TELA_INVENTARIO        6   /* chaves e progresso (tecla I)            */
#define TELA_CHAVE             7   /* chave obtida (US07, US11 e US14)        */
#define TELA_VITORIA           8   /* fim do jogo e "jogar novamente?"        */
#define TELA_CONFIRMAR_SAIDA   9   /* confirmacao antes de sair               */
#define TELA_ENCERRAR          10  /* encerra o game loop                     */
#define TELA_ARQUIVO           11  /* Fase 2: arquivo com o codigo (US08)     */
#define TELA_AVISO_PRIVACIDADE 12  /* Fase 2: aviso de privacidade (US09)     */
#define TELA_CODIGO            13  /* Fase 2: digitar o codigo (US10 e US11)  */
#define TELA_PISTA3            14  /* Fase 3: pista da decisao injusta (US12) */
#define TELA_RESULTADOS        15  /* Fase 3: resultados da IA (US13)         */
#define TELA_DECISAO           16  /* Fase 3: criterios da IA (US13 e US14)   */
#define TELA_PORTA_FINAL       17  /* Fase Final: porta de saida (US15)       */

/* ----------------------------------------------------------------------------
 * FASES
 * -------------------------------------------------------------------------- */
#define FASE_VERDADE      1   /* Central da Verdade: alucinacoes de IA       */
#define FASE_PRIVACIDADE  2   /* Setor de Privacidade: protecao de dados     */
#define FASE_JUSTICA      3   /* Nucleo da Justica: vies e decisoes          */
#define FASE_SAIDA        4   /* Fase Final: porta de saida                  */
#define FASE_INICIAL      FASE_VERDADE

/* ----------------------------------------------------------------------------
 * MENSAGENS DE RETORNO (exibidas no rodape, apos uma acao)
 * -------------------------------------------------------------------------- */
#define MSG_NENHUMA              0
#define MSG_PAREDE               1
#define MSG_NADA_PROXIMO         2
#define MSG_C1_BLOQUEADO         3
#define MSG_C2_BLOQUEADO         4
#define MSG_PORTA_TRANCADA       5
#define MSG_ACERTO               7
#define MSG_ERRO_P               8
#define MSG_ERRO_NAO_P           9
#define MSG_ERRO_TABELA          10
#define MSG_PORTA_ABERTA         11
#define MSG_CODIGO_GUARDADO      12
#define MSG_SISTEMA_BLOQUEADO    13
#define MSG_CODIGO_ERRADO        14
#define MSG_RESULTADOS_BLOQUEADO 15
#define MSG_DECISAO_BLOQUEADA    16
#define MSG_CRITERIO_LEGITIMO    17

/* ----------------------------------------------------------------------------
 * OBJETOS COM QUE O JOGADOR PODE INTERAGIR (tecla E)
 * Cada objeto pertence a uma fase; so os objetos da fase atual ficam ativos.
 * -------------------------------------------------------------------------- */
#define OBJ_NENHUM                0
#define OBJ_PISTA                 1    /* Fase 1 */
#define OBJ_COMPUTADOR1           2    /* Fase 1 */
#define OBJ_COMPUTADOR2           3    /* Fase 1 */
#define OBJ_PORTA                 4    /* Fase 1 */
#define OBJ_CHAVE                 5    /* Fase 1 */
#define OBJ_ARQUIVO1              6    /* Fase 2 */
#define OBJ_ARQUIVO2              7    /* Fase 2 */
#define OBJ_COMPUTADOR_BLOQUEADO  8    /* Fase 2 */
#define OBJ_PISTA3                9    /* Fase 3 */
#define OBJ_COMPUTADOR_DECISAO    10   /* Fase 3 */
#define OBJ_COMPUTADOR_RESULTADOS 11   /* Fase 3 */
#define OBJ_PORTA_FINAL           12   /* Fase Final */
#define TOTAL_OBJETOS             12

/* ----------------------------------------------------------------------------
 * MAPAS (7 linhas x 24 colunas)
 * Em vez de guardar os mapas em matrizes, cada posicao (linha, coluna) e
 * "calculada" por regras com if/else. Assim, o mesmo conjunto de regras
 * serve para desenhar o mapa E para testar colisoes.
 *
 *  FASE 1 - CENTRAL DA VERDADE            FASE 2 - SETOR DE PRIVACIDADE
 *  # # # # # # # # # # # # # # # # # # # # # # # #    # # # # # # # # # # # # # # # # # # # # # # # #
 *  # P . . . . . ? . . . . . . . # . . . . . . . #    # P . . . . . . A 1 . . . . . . . . . . . . . #
 *  # . # # # # . . . . . . . . . # . . . K . . . #    # . # # # # # . . . . . . . . # # # # # . . . #
 *  # . # . . . . . . . . . . . . D . . . . . . . #    # . . . . . . . . . . . A 2 . . . . . # . . . #
 *  # . # . . . C 1 . . . . . . . # . . . . . . . #    # . . . . . . . . . . . . . . . . . . # C . . #
 *  # . . . . . . . . C 2 . . . . # . . . . . . . #    # . . . . . . . . . . . . . . . . . . . . . . #
 *  # # # # # # # # # # # # # # # # # # # # # # # #    # # # # # # # # # # # # # # # # # # # # # # # #
 *
 *  FASE 3 - NUCLEO DA JUSTICA             FASE FINAL - SAIDA
 *  # # # # # # # # # # # # # # # # # # # # # # # #    # # # # # # # # # # # # # # # # # # # # # # # #
 *  # P . . . . . . ? . . . . . . . . . . . . . . #    # P . . . . . . . . . . . . . . . . . . . . . #
 *  # . # # # # . . . . . . . . . . . . . . . . . #    # . # # # # # # . . . # # # # # # . . . . . . #
 *  # . . . . . C 1 . . . . . # # # # . . . . . . #    # . . . . . . . . . . . . . . . . . . . . . . D
 *  # . . . . . . . . . . . . . C 2 . . . . . . . #    # . . . . . . . . . . . . . . . . . . . . . . #
 *  # . . . . . . . . . . . . . . . . . . . . . . #    # . . . . . . . . . . . . . . . . . . . . . . #
 *  # # # # # # # # # # # # # # # # # # # # # # # #    # # # # # # # # # # # # # # # # # # # # # # # #
 * -------------------------------------------------------------------------- */
#define ALTURA_MAPA       7
#define LARGURA_MAPA      24
#define INICIO_LINHA      1    /* posicao inicial do jogador em todas as fases */
#define INICIO_COLUNA     1

/* Fase 1 */
#define COLUNA_DIVISORIA  15   /* parede que separa a sala da chave         */
#define PISTA_LINHA       1
#define PISTA_COLUNA      7
#define C1_LINHA          4    /* computador C1 ocupa 2 casas: 'C' e '1'    */
#define C1_COLUNA         6
#define C2_LINHA          5    /* computador C2 ocupa 2 casas: 'C' e '2'    */
#define C2_COLUNA         9
#define PORTA_LINHA       3
#define PORTA_COLUNA      COLUNA_DIVISORIA
#define CHAVE_LINHA       2
#define CHAVE_COLUNA      19

/* Fase 2 */
#define A1_LINHA          1    /* arquivo A1 ocupa 2 casas: 'A' e '1'       */
#define A1_COLUNA         8
#define A2_LINHA          3    /* arquivo A2 ocupa 2 casas: 'A' e '2'       */
#define A2_COLUNA         12
#define CB_LINHA          4    /* computador bloqueado (1 casa: 'C')        */
#define CB_COLUNA         20

/* Fase 3 */
#define PISTA3_LINHA      1
#define PISTA3_COLUNA     8
#define DECISAO_LINHA     3    /* C1 - sistema de decisao (2 casas)         */
#define DECISAO_COLUNA    6
#define RESULTADOS_LINHA  4    /* C2 - resultados (2 casas)                 */
#define RESULTADOS_COLUNA 14

/* Fase Final */
#define PORTA_FINAL_LINHA   3
#define PORTA_FINAL_COLUNA  (LARGURA_MAPA - 1)   /* na parede da direita */

/* Simbolos do mapa */
#define PAREDE        '#'
#define CHAO          '.'
#define PISTA         '?'
#define COMPUTADOR    'C'
#define ARQUIVO       'A'
#define CHAVE         'K'
#define PORTA         'D'
#define PORTA_ABERTA  '/'

/* ----------------------------------------------------------------------------
 * REGRAS
 * -------------------------------------------------------------------------- */
#define ETAPAS_C1          2      /* Fase 1, C1: julgar p e depois ~p        */
#define LINHAS_TABELA      4      /* Fase 1, C2: tabela-verdade de p ^ q     */
#define CODIGO_ACESSO      2048   /* Fase 2: codigo que esta no arquivo A1   */
#define DIGITOS_CODIGO     4
#define CRITERIO_INADEQUADO '3'   /* Fase 3: "bairro onde mora"              */
#define TOTAL_CHAVES       3

/* ----------------------------------------------------------------------------
 * APARENCIA
 * Cores: o terminal entende sequencias que comecam com ESC (\033) e "[...m".
 * Ex.: "\033[92m" liga o verde; "\033[0m" volta ao normal. Como sao apenas
 * textos, entram no printf por concatenacao: printf(COR_OK "oi" COR_RESET).
 * Caracteres Unicode (bordas e blocos) tambem sao so texto dentro do printf.
 * Os simbolos da MATRIZ do mapa continuam sendo '#', '.', 'C'... (regras e
 * colisoes); so o DESENHO troca '#' por blocos, '.' por pontos e assim vai.
 * -------------------------------------------------------------------------- */
#define COR_RESET       "\033[0m"
#define COR_BORDA       "\033[36m"      /* ciano: molduras                     */
#define COR_TITULO      "\033[1;96m"    /* ciano brilhante em negrito: titulos */
#define COR_TECLA       "\033[1;93m"    /* amarelo em negrito: teclas [E]      */
#define COR_OK          "\033[1;92m"    /* verde: acertos                      */
#define COR_AVISO       "\033[93m"      /* amarelo: avisos                     */
#define COR_ERRO        "\033[1;91m"    /* vermelho: erros                     */
#define COR_DIM         "\033[90m"      /* cinza: detalhes                     */
#define COR_OURO        "\033[1;33m"    /* dourado: chaves                     */
#define COR_JOGADOR     "\033[1;97m"    /* branco em negrito: jogador          */
#define COR_PAREDE      "\033[34m"      /* azul: paredes                       */
#define COR_PISTA       "\033[1;95m"    /* magenta: pistas                     */
#define COR_COMPUTADOR  "\033[1;96m"    /* ciano: computadores                 */
#define COR_ARQUIVO     "\033[1;94m"    /* azul claro: arquivos                */
#define COR_PORTA       "\033[1;91m"    /* vermelho: porta trancada            */
#define COR_PORTA_ABERTA "\033[1;92m"   /* verde: porta aberta                 */

#define SIMBOLO_JOGADOR  "●"
#define SIMBOLO_PAREDE   "██"
#define SIMBOLO_CHAO     "· "

/* Molduras (largura interna: 50 caracteres) */
#define BARRA_DUPLA  "══════════════════════════════════════════════════"
#define BARRA_FINA   "──────────────────────────────────────────────────"
#define CAIXA_TOPO   " " COR_BORDA "╔" BARRA_DUPLA "╗" COR_RESET "\n"
#define CAIXA_BASE   " " COR_BORDA "╚" BARRA_DUPLA "╝" COR_RESET "\n"
#define CAIXA_ESQ    " " COR_BORDA "║" COR_RESET
#define CAIXA_DIR    COR_BORDA "║" COR_RESET "\n"
#define LINHA_FINA   " " COR_BORDA BARRA_FINA COR_RESET "\n"

int main(void) {
    /* ---------------- Estado do jogador ---------------- */
    int jogadorLinha = INICIO_LINHA;     /* posicao atual no mapa           */
    int jogadorColuna = INICIO_COLUNA;
    int faseAtual = FASE_INICIAL;        /* fase em que o jogador esta      */
    int chaveDaVerdade = 0;              /* 1 = chave obtida, 0 = nao       */
    int chaveDaPrivacidade = 0;
    int chaveDaJustica = 0;

    /* ---------------- Progresso da Fase 1 ---------------- */
    int pistaEncontrada = 0;             /* jogador ja leu a pista?         */
    int portaAberta = 0;                 /* porta D: C1 E C2 resolvidos     */

    /* ---------------- Progresso da Fase 3 ---------------- */
    int pista3Encontrada = 0;

    /* ---------------- Controle do jogo ---------------- */
    int telaAtual = TELA_MENU;           /* tela exibida neste momento      */
    int origemConfirmacao = TELA_MENU;   /* de onde veio o pedido de saida  */
    int reiniciarJogo = 0;               /* 1 = zerar o progresso do jogo   */
    int mensagem = MSG_NENHUMA;          /* mensagem do rodape              */

    /* ---------------- Entrada do usuario ---------------- */
    int teclaLida;                       /* codigo lido por _getch()        */
    char tecla = ' ';                    /* tecla ja convertida p/ maiuscula */
    int entradaValida;
    int tentativasInvalidas;

    /* ---------------- Movimento e desenho do mapa ---------------- */
    int destinoLinha = INICIO_LINHA;     /* para onde o jogador quer ir     */
    int destinoColuna = INICIO_COLUNA;
    int tentouMover = 0;                 /* ultima tecla foi W, A, S ou D?  */
    int passo;                           /* 0 = checar colisao, 1 = desenhar */
    int linha, coluna;
    char celula;                         /* simbolo calculado da posicao    */
    char celulaDestino = CHAO;           /* simbolo na casa de destino      */

    /* ---------------- Preparacao do terminal (aparencia) ---------------- */
    system("chcp 65001 > nul");   /* terminal passa a exibir Unicode (UTF-8)    */
    system("");                   /* garante o suporte a cores ANSI no Windows  */

    /* ========================================================================
     * GAME LOOP: repete ate o jogador escolher sair
     * ====================================================================== */
    while (telaAtual != TELA_ENCERRAR) {

        /* ------------------------------------------------------------------
         * (A) REINICIO DO JOGO
         * Um unico bloco zera o progresso. E usado tanto por "Iniciar jogo"
         * quanto por "Jogar novamente" (evita repetir codigo - DRY).
         * ---------------------------------------------------------------- */
        if (reiniciarJogo) {
            jogadorLinha = INICIO_LINHA;
            jogadorColuna = INICIO_COLUNA;
            destinoLinha = jogadorLinha;
            destinoColuna = jogadorColuna;
            faseAtual = FASE_INICIAL;
            chaveDaVerdade = 0;
            chaveDaPrivacidade = 0;
            chaveDaJustica = 0;
            pistaEncontrada = 0;
            portaAberta = 0;
            pista3Encontrada = 0;
            tentouMover = 0;
            mensagem = MSG_NENHUMA;
            reiniciarJogo = 0;
        }

        /* ------------------------------------------------------------------
         * (B) DESENHO DA TELA ATUAL
         * ---------------------------------------------------------------- */
        system("cls");   /* limpa a tela do terminal */

        /* Barra de status: aparece em todas as telas de jogo */
        if (telaAtual != TELA_MENU && telaAtual != TELA_INSTRUCOES &&
            telaAtual != TELA_VITORIA && telaAtual != TELA_CONFIRMAR_SAIDA) {
            printf(CAIXA_TOPO);
            if (faseAtual == FASE_VERDADE) {
                printf(CAIXA_ESQ COR_TITULO "  %-48s" COR_RESET CAIXA_DIR,
                       "NEXUS | FASE 1 - CENTRAL DA VERDADE");
            } else if (faseAtual == FASE_PRIVACIDADE) {
                printf(CAIXA_ESQ COR_TITULO "  %-48s" COR_RESET CAIXA_DIR,
                       "NEXUS | FASE 2 - SETOR DE PRIVACIDADE");
            } else if (faseAtual == FASE_JUSTICA) {
                printf(CAIXA_ESQ COR_TITULO "  %-48s" COR_RESET CAIXA_DIR,
                       "NEXUS | FASE 3 - NUCLEO DA JUSTICA");
            } else {
                printf(CAIXA_ESQ COR_TITULO "  %-48s" COR_RESET CAIXA_DIR,
                       "NEXUS | FASE FINAL - SAIDA DO SISTEMA");
            }
            printf(CAIXA_ESQ "  Chaves: " COR_OURO "%d/%d" COR_RESET "%37s" CAIXA_DIR,
                   chaveDaVerdade + chaveDaPrivacidade + chaveDaJustica, TOTAL_CHAVES, "");
            printf(CAIXA_BASE);
        }

        if (telaAtual == TELA_MENU) {
            /* ---------- MENU INICIAL (US01) ---------- */
            printf(CAIXA_TOPO);
            printf(CAIXA_ESQ COR_TITULO "%-50s" COR_RESET CAIXA_DIR,
                   "     _   _  _____ __  __ _   _  ____  ");
            printf(CAIXA_ESQ COR_TITULO "%-50s" COR_RESET CAIXA_DIR,
                   "    | \\ | || ____|\\ \\/ /| | | |/ ___| ");
            printf(CAIXA_ESQ COR_TITULO "%-50s" COR_RESET CAIXA_DIR,
                   "    |  \\| ||  _|   \\  / | | | |\\___ \\ ");
            printf(CAIXA_ESQ COR_TITULO "%-50s" COR_RESET CAIXA_DIR,
                   "    | |\\  || |___  /  \\ | |_| | ___) |");
            printf(CAIXA_ESQ COR_TITULO "%-50s" COR_RESET CAIXA_DIR,
                   "    |_| \\_||_____|/_/\\_\\ \\___/ |____/ ");
            printf(CAIXA_BASE);
            printf("  Voce esta preso em um sistema digital controlado\n");
            printf("  por uma Inteligencia Artificial chamada NEXUS.\n");
            printf("  Corrija os erros do sistema e reuna as tres chaves\n");
            printf("  para escapar.\n\n");
            printf("    " COR_TECLA "[1]" COR_RESET " INICIAR JOGO\n");
            printf("    " COR_TECLA "[2]" COR_RESET " INSTRUCOES\n");
            printf("    " COR_TECLA "[3]" COR_RESET " SAIR\n");

        } else if (telaAtual == TELA_INSTRUCOES) {
            /* ---------- INSTRUCOES (US02) ---------- */
            printf(CAIXA_TOPO);
            printf(CAIXA_ESQ COR_TITULO "  %-48s" COR_RESET CAIXA_DIR, "INSTRUCOES");
            printf(CAIXA_BASE);
            printf("  Basta apertar a tecla (nao e preciso apertar ENTER).\n\n");
            printf("    W - Cima            S - Baixo\n");
            printf("    A - Esquerda        D - Direita\n");
            printf("    Q - Sair\n\n");
            printf("  Simbolos do mapa:\n");
            printf("    " COR_JOGADOR SIMBOLO_JOGADOR COR_RESET " jogador   "
                   COR_PAREDE SIMBOLO_PAREDE COR_RESET " parede   "
                   COR_DIM "·" COR_RESET " chao   "
                   COR_PISTA "?" COR_RESET " pista\n");
            printf("    " COR_COMPUTADOR "C" COR_RESET " computador   "
                   COR_ARQUIVO "A" COR_RESET " arquivo   "
                   COR_PORTA "D" COR_RESET " porta   "
                   COR_OURO "K" COR_RESET " chave\n\n");
            printf("  Objetivo: passe pelas tres fases, corrija os erros da\n");
            printf("  IA, reuna as tres chaves e abra a porta de saida.\n\n");
            printf("  " COR_TECLA "[Qualquer tecla]" COR_RESET " Voltar ao menu\n");

        } else if (telaAtual == TELA_MAPA) {
            /* ---------- MAPA (US03 e US04) ---------- */
            /* Objetivo atual: muda conforme a fase e o progresso */
            printf("  " COR_TITULO "Objetivo: " COR_RESET);
            printf("explore o mapa.\n\n");

            /*
             * O mapa e percorrido DUAS vezes com as MESMAS regras (DRY):
             *   passo 0 -> descobre o simbolo da casa de destino e move o
             *              jogador se ela estiver livre (colisao);
             *   passo 1 -> desenha o mapa na tela.
             */
            for (passo = 0; passo < 2; passo++) {
                for (linha = 0; linha < ALTURA_MAPA; linha++) {
                    if (passo == 1) {
                        printf("   ");
                    }
                    for (coluna = 0; coluna < LARGURA_MAPA; coluna++) {
                        /* Regras do mapa: qual simbolo existe nesta posicao? */
                        if (faseAtual == FASE_SAIDA &&
                            linha == PORTA_FINAL_LINHA && coluna == PORTA_FINAL_COLUNA) {
                            celula = PORTA;                       /* porta final na borda */
                        } else if (linha == 0 || linha == ALTURA_MAPA - 1 ||
                                   coluna == 0 || coluna == LARGURA_MAPA - 1) {
                            celula = PAREDE;                      /* bordas */

                        } else if (faseAtual == FASE_VERDADE) {
                            if ((linha == 2 && coluna >= 2 && coluna <= 5) ||
                                (coluna == 2 && linha >= 3 && linha <= 4)) {
                                celula = PAREDE;
                            } else if (linha == PORTA_LINHA && coluna == PORTA_COLUNA) {
                                celula = portaAberta ? PORTA_ABERTA : PORTA;
                            } else if (coluna == COLUNA_DIVISORIA) {
                                celula = PAREDE;
                            } else if (linha == PISTA_LINHA && coluna == PISTA_COLUNA && !pistaEncontrada) {
                                celula = PISTA;
                            } else if (linha == C1_LINHA && coluna == C1_COLUNA) {
                                celula = COMPUTADOR;
                            } else if (linha == C1_LINHA && coluna == C1_COLUNA + 1) {
                                celula = '1';
                            } else if (linha == C2_LINHA && coluna == C2_COLUNA) {
                                celula = COMPUTADOR;
                            } else if (linha == C2_LINHA && coluna == C2_COLUNA + 1) {
                                celula = '2';
                            } else if (linha == CHAVE_LINHA && coluna == CHAVE_COLUNA && !chaveDaVerdade) {
                                celula = CHAVE;
                            } else {
                                celula = CHAO;
                            }

                        } else if (faseAtual == FASE_PRIVACIDADE) {
                            if ((linha == 2 && coluna >= 2 && coluna <= 6) ||
                                (linha == 2 && coluna >= 15 && coluna <= 19) ||
                                (coluna == 19 && linha >= 3 && linha <= 4)) {
                                celula = PAREDE;
                            } else if (linha == A1_LINHA && coluna == A1_COLUNA) {
                                celula = ARQUIVO;
                            } else if (linha == A1_LINHA && coluna == A1_COLUNA + 1) {
                                celula = '1';
                            } else if (linha == A2_LINHA && coluna == A2_COLUNA) {
                                celula = ARQUIVO;
                            } else if (linha == A2_LINHA && coluna == A2_COLUNA + 1) {
                                celula = '2';
                            } else if (linha == CB_LINHA && coluna == CB_COLUNA) {
                                celula = COMPUTADOR;
                            } else {
                                celula = CHAO;
                            }

                        } else if (faseAtual == FASE_JUSTICA) {
                            if ((linha == 2 && coluna >= 2 && coluna <= 5) ||
                                (linha == 3 && coluna >= 13 && coluna <= 16)) {
                                celula = PAREDE;
                            } else if (linha == PISTA3_LINHA && coluna == PISTA3_COLUNA && !pista3Encontrada) {
                                celula = PISTA;
                            } else if (linha == DECISAO_LINHA && coluna == DECISAO_COLUNA) {
                                celula = COMPUTADOR;
                            } else if (linha == DECISAO_LINHA && coluna == DECISAO_COLUNA + 1) {
                                celula = '1';
                            } else if (linha == RESULTADOS_LINHA && coluna == RESULTADOS_COLUNA) {
                                celula = COMPUTADOR;
                            } else if (linha == RESULTADOS_LINHA && coluna == RESULTADOS_COLUNA + 1) {
                                celula = '2';
                            } else {
                                celula = CHAO;
                            }

                        } else {   /* FASE_SAIDA */
                            if ((linha == 2 && coluna >= 2 && coluna <= 7) ||
                                (linha == 2 && coluna >= 11 && coluna <= 16)) {
                                celula = PAREDE;
                            } else {
                                celula = CHAO;
                            }
                        }

                        if (passo == 0) {
                            /* guarda o simbolo da casa para onde o jogador quer ir */
                            if (linha == destinoLinha && coluna == destinoColuna) {
                                celulaDestino = celula;
                            }
                        } else {
                            /* desenha (o jogador aparece por cima do chao) */
                            if (linha == jogadorLinha && coluna == jogadorColuna) {
                                printf(COR_JOGADOR SIMBOLO_JOGADOR COR_RESET " ");
                            } else if (celula == PAREDE) {
                                printf(COR_PAREDE SIMBOLO_PAREDE COR_RESET);
                            } else if (celula == CHAO) {
                                printf(COR_DIM SIMBOLO_CHAO COR_RESET);
                            } else if (celula == PISTA) {
                                printf(COR_PISTA "%c " COR_RESET, celula);
                            } else if (celula == CHAVE) {
                                printf(COR_OURO "%c " COR_RESET, celula);
                            } else if (celula == PORTA) {
                                printf(COR_PORTA "%c " COR_RESET, celula);
                            } else if (celula == PORTA_ABERTA) {
                                printf(COR_PORTA_ABERTA "%c " COR_RESET, celula);
                            } else if (celula == ARQUIVO ||
                                       (celula >= '1' && celula <= '2' &&
                                        faseAtual == FASE_PRIVACIDADE)) {
                                /* 'A' e o numero que vem depois dele (A1, A2) */
                                printf(COR_ARQUIVO "%c " COR_RESET, celula);
                            } else {
                                /* 'C' e o numero que vem depois dele (C1, C2) */
                                printf(COR_COMPUTADOR "%c " COR_RESET, celula);
                            }
                        }
                    }
                    if (passo == 1) {
                        printf("\n");
                    }
                }

                /* Fim do passo 0: aplica o movimento (nao atravessa obstaculos) */
                if (passo == 0 && tentouMover) {
                    if (celulaDestino == CHAO || celulaDestino == PORTA_ABERTA) {
                        jogadorLinha = destinoLinha;
                        jogadorColuna = destinoColuna;
                    } else {
                        mensagem = MSG_PAREDE;
                    }
                    tentouMover = 0;
                }
            }

            printf("\n  " COR_JOGADOR SIMBOLO_JOGADOR COR_RESET " voce  "
                   COR_PAREDE SIMBOLO_PAREDE COR_RESET " parede  "
                   COR_PISTA "?" COR_RESET " pista  "
                   COR_COMPUTADOR "C" COR_RESET " computador  "
                   COR_ARQUIVO "A" COR_RESET " arquivo\n");
            printf("  " COR_PORTA "D" COR_RESET " porta  "
                   COR_PORTA_ABERTA "/" COR_RESET " porta aberta  "
                   COR_OURO "K" COR_RESET " chave\n");
            printf(LINHA_FINA);
            printf("  " COR_TECLA "[W A S D]" COR_RESET " mover  " COR_TECLA "[Q]" COR_RESET " sair\n");

        } else if (telaAtual == TELA_CONFIRMAR_SAIDA) {
            /* ---------- CONFIRMAR SAIDA ---------- */
            if (origemConfirmacao == TELA_MENU) {
                printf("\n  Deseja realmente sair do NEXUS?\n\n");
            } else {
                printf("\n  Deseja voltar ao menu? O progresso sera perdido.\n\n");
            }
            printf("    " COR_TECLA "[S]" COR_RESET " Sim    " COR_TECLA "[N]" COR_RESET " Nao\n");
        }

        /* Mensagem do rodape: resultado da ultima acao */
        if (mensagem != MSG_NENHUMA) {
            if (mensagem == MSG_ACERTO || mensagem == MSG_PORTA_ABERTA ||
                mensagem == MSG_CODIGO_GUARDADO) {
                printf("\n  " COR_OK ">> ");                 /* acerto: verde   */
            } else if (mensagem == MSG_PAREDE || mensagem == MSG_NADA_PROXIMO ||
                       mensagem == MSG_C1_BLOQUEADO || mensagem == MSG_C2_BLOQUEADO ||
                       mensagem == MSG_PORTA_TRANCADA || mensagem == MSG_SISTEMA_BLOQUEADO ||
                       mensagem == MSG_RESULTADOS_BLOQUEADO ||
                       mensagem == MSG_DECISAO_BLOQUEADA) {
                printf("\n  " COR_AVISO ">> ");              /* aviso: amarelo  */
            } else {
                printf("\n  " COR_ERRO ">> ");               /* erro: vermelho  */
            }
            if (mensagem == MSG_PAREDE) {
                printf("Caminho bloqueado! Voce nao pode atravessar obstaculos.\n");
            }
            printf(COR_RESET);
            mensagem = MSG_NENHUMA;   /* cada mensagem aparece uma unica vez */
        }

        /* ------------------------------------------------------------------
         * (C) LEITURA E VALIDACAO DA TECLA (sem ENTER)
         * O laco while so termina quando a tecla for valida para a tela
         * atual. Teclas erradas nunca travam nem encerram o programa.
         * ---------------------------------------------------------------- */
        printf("\n  " COR_DIM "Teclas aceitas: ");
        if (telaAtual == TELA_MENU || telaAtual == TELA_VITORIA) {
            printf("1, 2 ou 3\n");
        } else if (telaAtual == TELA_INSTRUCOES) {
            printf("qualquer tecla\n");
        } else if (telaAtual == TELA_MAPA) {
            printf("W, A, S, D ou Q\n");
        } else {
            printf("S ou N\n");
        }

        printf(COR_RESET);
        entradaValida = 0;
        tentativasInvalidas = 0;
        while (!entradaValida) {
            teclaLida = _getch();          /* le a tecla sem esperar ENTER */

            /* Setas e teclas de funcao enviam dois codigos: descarta os dois */
            if (teclaLida == TECLA_ESPECIAL_1 || teclaLida == TECLA_ESPECIAL_2) {
                teclaLida = _getch();
                teclaLida = ' ';
            }

            tecla = (char) teclaLida;

            /* converte minuscula em maiuscula: 'w' -> 'W' */
            if (tecla >= 'a' && tecla <= 'z') {
                tecla -= ('a' - 'A');
            }

            /* A tecla e valida para a tela atual? */
            if (tecla == ' ' || tecla == '\n' || tecla == '\r' || tecla == '\t') {
                entradaValida = 0;           /* espacos, ENTER e setas sao ignorados */
            } else if (telaAtual == TELA_MENU || telaAtual == TELA_VITORIA) {
                entradaValida = (tecla >= '1' && tecla <= '3');
            } else if (telaAtual == TELA_INSTRUCOES) {
                entradaValida = 1;
            } else if (telaAtual == TELA_MAPA) {
                entradaValida = (tecla == 'W' || tecla == 'A' || tecla == 'S' ||
                                 tecla == 'D' || tecla == 'Q');
            } else {
                entradaValida = (tecla == 'S' || tecla == 'N');
            }

            /* Aviso para teclas invalidas (espacos, ENTER e setas nao contam) */
            if (!entradaValida && tecla != ' ' && tecla != '\n' &&
                tecla != '\r' && tecla != '\t') {
                tentativasInvalidas++;
                printf("  " COR_ERRO "Tecla '%c' invalida!" COR_RESET " Tente novamente. (avisos: %d)\n",
                       tecla, tentativasInvalidas);
            }
        }

        /* ------------------------------------------------------------------
         * (D) PROCESSAMENTO DA TECLA
         * Usamos if / else if: apenas o bloco da tela atual e executado.
         * ---------------------------------------------------------------- */
        if (telaAtual == TELA_MENU) {
            /* 1 = iniciar, 2 = instrucoes, 3 = sair (com confirmacao) */
            if (tecla == '1') {
                reiniciarJogo = 1;
                telaAtual = TELA_MAPA;
            } else if (tecla == '2') {
                telaAtual = TELA_INSTRUCOES;
            } else {
                origemConfirmacao = TELA_MENU;
                telaAtual = TELA_CONFIRMAR_SAIDA;
            }

        } else if (telaAtual == TELA_INSTRUCOES) {
            telaAtual = TELA_MENU;               /* qualquer tecla volta */

        } else if (telaAtual == TELA_MAPA) {
            if (tecla == 'W' || tecla == 'A' || tecla == 'S' || tecla == 'D') {
                /* Movimento: (tecla == 'S') vale 1 se verdadeiro e 0 se falso.
                 * A colisao e verificada no passo 0 do desenho do mapa. */
                destinoLinha = jogadorLinha + (tecla == 'S') - (tecla == 'W');
                destinoColuna = jogadorColuna + (tecla == 'D') - (tecla == 'A');
                tentouMover = 1;

            } else {                              /* Q */
                origemConfirmacao = TELA_MAPA;
                telaAtual = TELA_CONFIRMAR_SAIDA;
            }

        } else if (telaAtual == TELA_CONFIRMAR_SAIDA) {
            /* S confirma; N volta para a tela de origem */
            if (tecla == 'N') {
                telaAtual = origemConfirmacao;
            } else if (origemConfirmacao == TELA_MENU) {
                telaAtual = TELA_ENCERRAR;
            } else {
                telaAtual = TELA_MENU;
            }
        }
    }

    printf("\n  Obrigado por jogar NEXUS! Ate a proxima.\n\n");
    return 0;
}
