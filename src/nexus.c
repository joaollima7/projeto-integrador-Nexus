/*
 * ============================================================================
 *  NEXUS - Jogo educativo de aventura e exploracao no terminal
 *  Projeto Integrador - CESAR School
 *  Versao completa: Menu + Fase 1 (Central da Verdade) + Fase 2 (Setor de
 *  Privacidade) + Fase 3 (Nucleo da Justica) + Fase Final (Saida)
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
    int respostasIncorretas = 0;         /* usado no resumo final           */

    /* ---------------- Progresso da Fase 1 ---------------- */
    int pistaEncontrada = 0;             /* jogador ja leu a pista?         */
    int etapaComputador1 = 0;            /* 0 = julgar p, 1 = julgar ~p     */
    int linhaTabela = 0;                 /* linha atual da tabela no C2     */
    int computador1Resolvido = 0;
    int computador2Resolvido = 0;
    int portaAberta = 0;                 /* porta D: C1 E C2 resolvidos     */

    /* ---------------- Progresso da Fase 2 ---------------- */
    int codigoEncontrado = 0;            /* jogador guardou o codigo?       */
    int codigoDigitado = 0;              /* numero formado pelos digitos    */
    int digitosDigitados = 0;            /* quantos digitos ja foram teclados */

    /* ---------------- Progresso da Fase 3 ---------------- */
    int pista3Encontrada = 0;
    int resultadosVistos = 0;            /* jogador ja viu o computador C2? */

    /* ---------------- Controle do jogo ---------------- */
    int telaAtual = TELA_MENU;           /* tela exibida neste momento      */
    int telaRetorno = TELA_MAPA;         /* para onde o aviso de privacidade volta */
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

    /* ---------------- Interacao e computadores ---------------- */
    int objeto, objetoProximo;
    int objetoLinha, objetoColuna, objetoLargura;
    int objetoAtivo, pertoDoObjeto;
    char respostaEsperada;
    int linhaExibida, valorP, valorQ;    /* linhas da tabela-verdade        */
    int todasAsChaves;                   /* 1 = as tres chaves foram obtidas */

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
            respostasIncorretas = 0;
            pistaEncontrada = 0;
            etapaComputador1 = 0;
            linhaTabela = 0;
            computador1Resolvido = 0;
            computador2Resolvido = 0;
            portaAberta = 0;
            codigoEncontrado = 0;
            codigoDigitado = 0;
            digitosDigitados = 0;
            pista3Encontrada = 0;
            resultadosVistos = 0;
            tentouMover = 0;
            mensagem = MSG_NENHUMA;
            reiniciarJogo = 0;
        }

        todasAsChaves = chaveDaVerdade && chaveDaPrivacidade && chaveDaJustica;

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
            printf("    E - Interagir com um objeto proximo\n");
            printf("    I - Inventario\n");
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
            if (faseAtual == FASE_VERDADE) {
                if (!pistaEncontrada) {
                    printf("explore a sala e encontre a pista (?).\n\n");
                } else if (!computador1Resolvido) {
                    printf("investigue o computador C1.\n\n");
                } else if (!computador2Resolvido) {
                    printf("corrija o filtro do computador C2.\n\n");
                } else {
                    printf("a porta D esta aberta! Pegue a chave K.\n\n");
                }
            } else if (faseAtual == FASE_PRIVACIDADE) {
                if (!codigoEncontrado) {
                    printf("procure o codigo de acesso nos arquivos (A).\n\n");
                } else {
                    printf("use o codigo no computador bloqueado (C).\n\n");
                }
            } else if (faseAtual == FASE_JUSTICA) {
                if (!pista3Encontrada) {
                    printf("encontre a pista (?).\n\n");
                } else if (!resultadosVistos) {
                    printf("veja os resultados no computador C2.\n\n");
                } else {
                    printf("corrija o sistema de decisao no computador C1.\n\n");
                }
            } else {
                printf("va ate a porta D e abra a saida.\n\n");
            }

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
            printf("  " COR_TECLA "[W A S D]" COR_RESET " mover  " COR_TECLA "[E]" COR_RESET " interagir  " COR_TECLA "[I]" COR_RESET " inventario  " COR_TECLA "[Q]" COR_RESET " sair\n");

        } else if (telaAtual == TELA_PISTA) {
            /* ---------- FASE 1: PISTA (US05) ---------- */
            printf("  " COR_OK "PISTA ENCONTRADA!" COR_RESET "\n\n");
            printf("  Um bilhete do tecnico de plantao diz:\n\n");
            printf("     \"O servidor principal foi desligado as 22h.\"\n\n");
            printf("  Guarde essa informacao: a IA NEXUS pode afirmar o\n");
            printf("  contrario. Quando uma IA afirma algo falso como se\n");
            printf("  fosse verdade, chamamos isso de ALUCINACAO.\n\n");
            printf("  Investigue o computador C1.\n\n");
            printf("  " COR_TECLA "[E]" COR_RESET " Continuar\n");

        } else if (telaAtual == TELA_COMPUTADOR1) {
            /* ---------- FASE 1: COMPUTADOR C1 - afirmacoes da IA (US06) ---------- */
            printf("  " COR_TITULO "COMPUTADOR C1 - AFIRMACOES DA IA NEXUS" COR_RESET "\n");
            printf(LINHA_FINA);
            printf("  Pista: \"O servidor principal foi desligado as 22h.\"\n\n");
            printf("  A IA NEXUS afirma:\n");
            printf("   p : \"O servidor principal esta ligado.\"\n");
            printf("       Valor logico: %c\n", etapaComputador1 > 0 ? 'F' : '?');
            printf("   ~p: \"Nao e verdade que o servidor principal\n");
            printf("        esta ligado.\"\n");
            printf("       Valor logico: %c\n\n", etapaComputador1 > 1 ? 'V' : '?');

            if (etapaComputador1 == 0) {
                printf("  Qual o valor logico de p?\n");
                printf("  " COR_TECLA "[V]" COR_RESET " Verdadeiro  " COR_TECLA "[F]" COR_RESET " Falso  " COR_TECLA "[Q]" COR_RESET " Sair do computador\n");
            } else if (etapaComputador1 == 1) {
                printf("  Qual o valor logico de ~p (negacao de p)?\n");
                printf("  " COR_TECLA "[V]" COR_RESET " Verdadeiro  " COR_TECLA "[F]" COR_RESET " Falso  " COR_TECLA "[Q]" COR_RESET " Sair do computador\n");
            } else {
                printf("  SISTEMA CORRIGIDO! A afirmacao p era uma ALUCINACAO:\n");
                printf("  parecia certa, mas contradiz a pista.\n\n");
                printf("  " COR_TECLA "[E]" COR_RESET " Voltar ao mapa\n");
            }

        } else if (telaAtual == TELA_COMPUTADOR2) {
            /* ---------- FASE 1: COMPUTADOR C2 - filtro de confianca (US07) ---------- */
            printf("  " COR_TITULO "COMPUTADOR C2 - FILTRO DE CONFIANCA" COR_RESET "\n");
            printf(LINHA_FINA);
            printf("  Uma resposta da IA so e CONFIAVEL se:\n");
            printf("    p = \"a resposta cita uma fonte\"\n");
            printf("    q = \"o dado confere com as pistas\"\n");
            printf("    confiavel = p ^ q   (conjuncao \"E\"; em C: p && q)\n\n");
            printf("  Complete a ultima coluna da tabela-verdade:\n\n");
            printf("       p | q | p ^ q\n");
            printf("      ---+---+-------\n");
            for (linhaExibida = 0; linhaExibida < LINHAS_TABELA; linhaExibida++) {
                valorP = (linhaExibida < 2);           /* linhas 0 e 1: p = V */
                valorQ = (linhaExibida % 2 == 0);      /* linhas pares: q = V */
                printf("       %c | %c |   ", valorP ? 'V' : 'F', valorQ ? 'V' : 'F');
                if (linhaExibida < linhaTabela) {
                    printf("%c\n", (valorP && valorQ) ? 'V' : 'F');   /* ja respondida */
                } else if (linhaExibida == linhaTabela) {
                    printf("?   <- sua vez\n");
                } else {
                    printf("?\n");
                }
            }

            if (linhaTabela < LINHAS_TABELA) {
                printf("\n  Qual o valor de p ^ q nessa linha?\n");
                printf("  " COR_TECLA "[V]" COR_RESET " Verdadeiro  " COR_TECLA "[F]" COR_RESET " Falso  " COR_TECLA "[Q]" COR_RESET " Sair do computador\n");
            } else {
                printf("\n  FILTRO CORRIGIDO! A porta D foi destrancada.\n\n");
                printf("  " COR_TECLA "[E]" COR_RESET " Voltar ao mapa\n");
            }

        } else if (telaAtual == TELA_ARQUIVO) {
            /* ---------- FASE 2: ARQUIVO A1 (US08 e US10) ---------- */
            printf("  " COR_TITULO "ARQUIVO A1 - acesso_sistema.txt" COR_RESET "\n");
            printf(LINHA_FINA);
            printf("  Conteudo do arquivo:\n");
            printf("    Codigo de acesso: %d        " COR_OK "[NECESSARIO]" COR_RESET "\n", CODIGO_ACESSO);
            printf("    CPF do funcionario: ***     " COR_ERRO "[DADO PESSOAL]" COR_RESET "\n");
            printf("    Endereco residencial: ***   " COR_ERRO "[DADO PESSOAL]" COR_RESET "\n\n");
            if (!codigoEncontrado) {
                printf("  O que voce quer guardar para a missao?\n");
                printf("    " COR_TECLA "[1]" COR_RESET " Apenas o codigo de acesso\n");
                printf("    " COR_TECLA "[2]" COR_RESET " O arquivo inteiro, com os dados pessoais\n");
                printf("    " COR_TECLA "[Q]" COR_RESET " Fechar o arquivo\n");
            } else {
                printf("  Codigo de acesso guardado: %d\n", CODIGO_ACESSO);
                printf("  Os dados pessoais ficaram protegidos.\n\n");
                printf("  " COR_TECLA "[E]" COR_RESET " Voltar ao mapa\n");
            }

        } else if (telaAtual == TELA_AVISO_PRIVACIDADE) {
            /* ---------- FASE 2: AVISO DE PRIVACIDADE (US09) ---------- */
            printf("  " COR_ERRO "!!! AVISO DE PRIVACIDADE !!!" COR_RESET "\n");
            printf(LINHA_FINA);
            printf("  Voce tentou acessar DADOS PESSOAIS (CPF, endereco,\n");
            printf("  telefone) que NAO sao necessarios para a missao.\n\n");
            printf("  Um sistema de IA deve usar apenas os dados de que\n");
            printf("  realmente precisa. Coletar dados pessoais sem\n");
            printf("  necessidade coloca a privacidade das pessoas em risco.\n\n");
            printf("  " COR_TECLA "[E]" COR_RESET " Entendido\n");

        } else if (telaAtual == TELA_CODIGO) {
            /* ---------- FASE 2: COMPUTADOR BLOQUEADO (US10 e US11) ---------- */
            printf("  " COR_TITULO "COMPUTADOR C - SISTEMA BLOQUEADO" COR_RESET "\n");
            printf(LINHA_FINA);
            printf("  Este computador guarda dados pessoais sem necessidade.\n");
            printf("  Digite o codigo de acesso para desbloquear o sistema\n");
            printf("  e ativar a protecao de dados.\n\n");
            printf("  Codigo: [ ");
            if (digitosDigitados > 0) {
                printf("%0*d", digitosDigitados, codigoDigitado);   /* digitos ja teclados */
            }
            for (linhaExibida = digitosDigitados; linhaExibida < DIGITOS_CODIGO; linhaExibida++) {
                printf("_");                                         /* digitos que faltam  */
            }
            printf(" ]\n\n");
            printf("  " COR_TECLA "[0-9]" COR_RESET " Digitar o codigo   " COR_TECLA "[Q]" COR_RESET " Sair do computador\n");

        } else if (telaAtual == TELA_PISTA3) {
            /* ---------- FASE 3: PISTA (US12) ---------- */
            printf("  " COR_OK "PISTA ENCONTRADA!" COR_RESET "\n\n");
            printf("  Uma mensagem no chao diz:\n\n");
            printf("     \"O sistema esta utilizando uma informacao\n");
            printf("      inadequada para tomar uma decisao.\"\n\n");
            printf("  Quando uma IA usa dados que nao deveriam influenciar\n");
            printf("  uma decisao, ela pode ser INJUSTA. Isso e chamado de\n");
            printf("  VIES.\n\n");
            printf("  Veja os resultados no computador C2.\n\n");
            printf("  " COR_TECLA "[E]" COR_RESET " Continuar\n");

        } else if (telaAtual == TELA_RESULTADOS) {
            /* ---------- FASE 3: COMPUTADOR C2 - resultados (US13) ---------- */
            printf("  " COR_TITULO "COMPUTADOR C2 - RESULTADOS DA IA" COR_RESET "\n");
            printf(LINHA_FINA);
            printf("  Pedidos de bolsa de estudo:\n\n");
            printf("    Ana   - nota 9.0 - frequencia 95%% - bairro X  RECUSADA\n");
            printf("    Bruno - nota 6.0 - frequencia 80%% - bairro Y  APROVADO\n\n");
            printf("  Por que a aluna com a maior nota foi recusada?\n");
            printf("  Veja os criterios no computador C1.\n\n");
            printf("  " COR_TECLA "[E]" COR_RESET " Voltar ao mapa\n");

        } else if (telaAtual == TELA_DECISAO) {
            /* ---------- FASE 3: COMPUTADOR C1 - sistema de decisao (US13 e US14) ---------- */
            printf("  " COR_TITULO "COMPUTADOR C1 - SISTEMA DE DECISAO" COR_RESET "\n");
            printf(LINHA_FINA);
            printf("  Criterios usados pela IA para aprovar a bolsa:\n\n");
            printf("    " COR_TECLA "[1]" COR_RESET " Nota do aluno\n");
            printf("    " COR_TECLA "[2]" COR_RESET " Frequencia nas aulas\n");
            printf("    " COR_TECLA "[3]" COR_RESET " Bairro onde o aluno mora\n\n");
            printf("  Qual criterio e INADEQUADO e deve ser removido?\n");
            printf("  " COR_TECLA "[1]" COR_RESET " " COR_TECLA "[2]" COR_RESET " " COR_TECLA "[3]" COR_RESET " Escolher     " COR_TECLA "[Q]" COR_RESET " Sair do computador\n");

        } else if (telaAtual == TELA_INVENTARIO) {
            /* ---------- INVENTARIO (tecla I) ---------- */
            printf("  " COR_TITULO "INVENTARIO" COR_RESET "\n");
            printf(LINHA_FINA);
            printf("   %s[%c]" COR_RESET " Chave da Verdade\n",
                   chaveDaVerdade ? COR_OK : COR_DIM, chaveDaVerdade ? 'X' : ' ');
            printf("   %s[%c]" COR_RESET " Chave da Privacidade\n",
                   chaveDaPrivacidade ? COR_OK : COR_DIM, chaveDaPrivacidade ? 'X' : ' ');
            printf("   %s[%c]" COR_RESET " Chave da Justica\n\n",
                   chaveDaJustica ? COR_OK : COR_DIM, chaveDaJustica ? 'X' : ' ');
            if (faseAtual == FASE_PRIVACIDADE) {
                printf("   Codigo de acesso: %s\n\n", codigoEncontrado ? "2048" : "nao encontrado");
            }
            printf("  " COR_TECLA "[I]" COR_RESET " Fechar inventario\n");

        } else if (telaAtual == TELA_CHAVE) {
            /* ---------- CHAVE OBTIDA (US07, US11 e US14) ---------- */
            if (faseAtual == FASE_VERDADE) {
                printf("  " COR_OURO "*** CHAVE DA VERDADE OBTIDA! ***" COR_RESET "\n\n");
                printf("  A Central da Verdade voltou a funcionar.\n\n");
                printf("  Licao: uma IA pode \"alucinar\" e afirmar algo falso\n");
                printf("  com confianca. Sempre confira as respostas com\n");
                printf("  fontes e informacoes confiaveis.\n\n");
            } else if (faseAtual == FASE_PRIVACIDADE) {
                printf("  " COR_OURO "*** CHAVE DA PRIVACIDADE OBTIDA! ***" COR_RESET "\n\n");
                printf("  Sistema desbloqueado: os dados pessoais desnecessarios\n");
                printf("  foram protegidos.\n\n");
                printf("  Licao: uma IA deve usar apenas os dados de que\n");
                printf("  realmente precisa para cumprir sua tarefa.\n\n");
            } else {
                printf("  " COR_OURO "*** CHAVE DA JUSTICA OBTIDA! ***" COR_RESET "\n\n");
                printf("  O criterio \"bairro\" foi removido. Ana agora e\n");
                printf("  aprovada pela sua nota.\n\n");
                printf("  Licao: decisoes automatizadas precisam usar criterios\n");
                printf("  justos. Dados inadequados geram VIES.\n\n");
            }
            printf("  Item adicionado ao inventario.\n\n");
            printf("  " COR_TECLA "[E]" COR_RESET " Continuar\n");

        } else if (telaAtual == TELA_PORTA_FINAL) {
            /* ---------- FASE FINAL: PORTA DE SAIDA (US15) ---------- */
            printf("  " COR_TITULO "PORTA FINAL - SAIDA DO SISTEMA NEXUS" COR_RESET "\n");
            printf(LINHA_FINA);
            printf("  Verificando chaves...\n\n");
            printf("   %s[%s]" COR_RESET " Chave da Verdade\n",
                   chaveDaVerdade ? COR_OK : COR_DIM, chaveDaVerdade ? "OK" : "  ");
            printf("   %s[%s]" COR_RESET " Chave da Privacidade\n",
                   chaveDaPrivacidade ? COR_OK : COR_DIM, chaveDaPrivacidade ? "OK" : "  ");
            printf("   %s[%s]" COR_RESET " Chave da Justica\n\n",
                   chaveDaJustica ? COR_OK : COR_DIM, chaveDaJustica ? "OK" : "  ");
            if (todasAsChaves) {
                printf("  Todas as chaves foram encontradas!\n\n");
                printf("  " COR_TECLA "[E]" COR_RESET " Abrir a porta    " COR_TECLA "[Q]" COR_RESET " Voltar\n");
            } else {
                printf("  A porta so abre com as tres chaves.\n\n");
                printf("  " COR_TECLA "[Q]" COR_RESET " Voltar\n");
            }

        } else if (telaAtual == TELA_VITORIA) {
            /* ---------- VITORIA - jogar novamente? (US15) ---------- */
            printf(CAIXA_TOPO);
            printf(CAIXA_ESQ COR_OK "  %-48s" COR_RESET CAIXA_DIR,
                   "A PORTA SE ABRIU... VOCE ESCAPOU DO NEXUS!");
            printf(CAIXA_BASE);
            printf("  Voce corrigiu os erros da IA:\n");
            printf("    - informacoes falsas (alucinacao)\n");
            printf("    - uso indevido de dados pessoais (privacidade)\n");
            printf("    - decisoes injustas (vies)\n\n");
            printf("  Respostas incorretas: %d\n", respostasIncorretas);
            printf("  Desempenho:           ");
            if (respostasIncorretas == 0) {
                printf("perfeito!\n\n");
            } else if (respostasIncorretas <= 3) {
                printf("muito bom!\n\n");
            } else {
                printf("continue praticando!\n\n");
            }
            printf("  Deseja jogar novamente?\n");
            printf("    " COR_TECLA "[1]" COR_RESET " Jogar novamente\n");
            printf("    " COR_TECLA "[2]" COR_RESET " Voltar ao menu\n");
            printf("    " COR_TECLA "[3]" COR_RESET " Sair do jogo\n");

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
            } else if (mensagem == MSG_NADA_PROXIMO) {
                printf("Nada para interagir aqui. Chegue perto de ?, C, A, D ou K.\n");
            } else if (mensagem == MSG_C1_BLOQUEADO) {
                printf("O computador C1 esta bloqueado. Encontre a pista (?) primeiro.\n");
            } else if (mensagem == MSG_C2_BLOQUEADO) {
                printf("Acesso negado ao C2. Primeiro corrija as afirmacoes do C1.\n");
            } else if (mensagem == MSG_PORTA_TRANCADA) {
                printf("Porta D trancada: ela so abre se C1 E C2 estiverem corrigidos.\n");
            } else if (mensagem == MSG_ACERTO) {
                printf("Correto!\n");
            } else if (mensagem == MSG_ERRO_P) {
                printf("Incorreto. A pista diz que o servidor foi DESLIGADO, entao p e Falsa.\n");
            } else if (mensagem == MSG_ERRO_NAO_P) {
                printf("Incorreto. A negacao inverte o valor: se p = F, entao ~p = V.\n");
            } else if (mensagem == MSG_ERRO_TABELA) {
                printf("Incorreto. p ^ q so e V quando p E q sao V ao mesmo tempo.\n");
            } else if (mensagem == MSG_PORTA_ABERTA) {
                printf("Correto! A porta D foi DESTRANCADA.\n");
            } else if (mensagem == MSG_CODIGO_GUARDADO) {
                printf("Codigo guardado! Voce usou apenas o dado necessario.\n");
            } else if (mensagem == MSG_SISTEMA_BLOQUEADO) {
                printf("Sistema bloqueado: encontre o codigo de acesso em um arquivo (A).\n");
            } else if (mensagem == MSG_CODIGO_ERRADO) {
                printf("Codigo incorreto! Confira o codigo guardado no inventario (I).\n");
            } else if (mensagem == MSG_RESULTADOS_BLOQUEADO) {
                printf("O computador C2 esta bloqueado. Encontre a pista (?) primeiro.\n");
            } else if (mensagem == MSG_DECISAO_BLOQUEADA) {
                printf("Primeiro veja os resultados da IA no computador C2.\n");
            } else {
                printf("Esse criterio e justo. Procure o que NAO deveria influenciar.\n");
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
            printf("W, A, S, D, E, I ou Q\n");
        } else if (telaAtual == TELA_PISTA || telaAtual == TELA_CHAVE ||
                   telaAtual == TELA_AVISO_PRIVACIDADE || telaAtual == TELA_PISTA3 ||
                   telaAtual == TELA_RESULTADOS) {
            printf("E\n");
        } else if (telaAtual == TELA_COMPUTADOR1) {
            printf("%s\n", computador1Resolvido ? "E ou Q" : "V, F ou Q");
        } else if (telaAtual == TELA_COMPUTADOR2) {
            printf("%s\n", computador2Resolvido ? "E ou Q" : "V, F ou Q");
        } else if (telaAtual == TELA_ARQUIVO) {
            printf("%s\n", codigoEncontrado ? "E ou Q" : "1, 2 ou Q");
        } else if (telaAtual == TELA_CODIGO) {
            printf("0 a 9 ou Q\n");
        } else if (telaAtual == TELA_DECISAO) {
            printf("1, 2, 3 ou Q\n");
        } else if (telaAtual == TELA_PORTA_FINAL) {
            printf("%s\n", todasAsChaves ? "E ou Q" : "Q");
        } else if (telaAtual == TELA_INVENTARIO) {
            printf("I ou Q\n");
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
                                 tecla == 'D' || tecla == 'E' || tecla == 'I' ||
                                 tecla == 'Q');
            } else if (telaAtual == TELA_PISTA || telaAtual == TELA_CHAVE ||
                       telaAtual == TELA_AVISO_PRIVACIDADE || telaAtual == TELA_PISTA3 ||
                       telaAtual == TELA_RESULTADOS) {
                entradaValida = (tecla == 'E');
            } else if (telaAtual == TELA_COMPUTADOR1) {
                if (computador1Resolvido) {
                    entradaValida = (tecla == 'E' || tecla == 'Q');
                } else {
                    entradaValida = (tecla == 'V' || tecla == 'F' || tecla == 'Q');
                }
            } else if (telaAtual == TELA_COMPUTADOR2) {
                if (computador2Resolvido) {
                    entradaValida = (tecla == 'E' || tecla == 'Q');
                } else {
                    entradaValida = (tecla == 'V' || tecla == 'F' || tecla == 'Q');
                }
            } else if (telaAtual == TELA_ARQUIVO) {
                if (codigoEncontrado) {
                    entradaValida = (tecla == 'E' || tecla == 'Q');
                } else {
                    entradaValida = (tecla == '1' || tecla == '2' || tecla == 'Q');
                }
            } else if (telaAtual == TELA_CODIGO) {
                entradaValida = ((tecla >= '0' && tecla <= '9') || tecla == 'Q');
            } else if (telaAtual == TELA_DECISAO) {
                entradaValida = ((tecla >= '1' && tecla <= '3') || tecla == 'Q');
            } else if (telaAtual == TELA_PORTA_FINAL) {
                entradaValida = (tecla == 'Q' || (tecla == 'E' && todasAsChaves));
            } else if (telaAtual == TELA_INVENTARIO) {
                entradaValida = (tecla == 'I' || tecla == 'Q');
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

            } else if (tecla == 'E') {
                /* Interacao: procura um objeto ativo ao redor do jogador.
                 * Um unico laco testa todos os objetos (DRY); so os objetos
                 * da fase atual ficam ativos. */
                objetoProximo = OBJ_NENHUM;
                for (objeto = 1; objeto <= TOTAL_OBJETOS; objeto++) {
                    objetoLargura = 1;
                    if (objeto == OBJ_PISTA) {
                        objetoLinha = PISTA_LINHA;
                        objetoColuna = PISTA_COLUNA;
                        objetoAtivo = (faseAtual == FASE_VERDADE) && !pistaEncontrada;
                    } else if (objeto == OBJ_COMPUTADOR1) {
                        objetoLinha = C1_LINHA;
                        objetoColuna = C1_COLUNA;
                        objetoLargura = 2;
                        objetoAtivo = (faseAtual == FASE_VERDADE);
                    } else if (objeto == OBJ_COMPUTADOR2) {
                        objetoLinha = C2_LINHA;
                        objetoColuna = C2_COLUNA;
                        objetoLargura = 2;
                        objetoAtivo = (faseAtual == FASE_VERDADE);
                    } else if (objeto == OBJ_PORTA) {
                        objetoLinha = PORTA_LINHA;
                        objetoColuna = PORTA_COLUNA;
                        objetoAtivo = (faseAtual == FASE_VERDADE) && !portaAberta;
                    } else if (objeto == OBJ_CHAVE) {
                        objetoLinha = CHAVE_LINHA;
                        objetoColuna = CHAVE_COLUNA;
                        objetoAtivo = (faseAtual == FASE_VERDADE) && portaAberta && !chaveDaVerdade;
                    } else if (objeto == OBJ_ARQUIVO1) {
                        objetoLinha = A1_LINHA;
                        objetoColuna = A1_COLUNA;
                        objetoLargura = 2;
                        objetoAtivo = (faseAtual == FASE_PRIVACIDADE);
                    } else if (objeto == OBJ_ARQUIVO2) {
                        objetoLinha = A2_LINHA;
                        objetoColuna = A2_COLUNA;
                        objetoLargura = 2;
                        objetoAtivo = (faseAtual == FASE_PRIVACIDADE);
                    } else if (objeto == OBJ_COMPUTADOR_BLOQUEADO) {
                        objetoLinha = CB_LINHA;
                        objetoColuna = CB_COLUNA;
                        objetoAtivo = (faseAtual == FASE_PRIVACIDADE);
                    } else if (objeto == OBJ_PISTA3) {
                        objetoLinha = PISTA3_LINHA;
                        objetoColuna = PISTA3_COLUNA;
                        objetoAtivo = (faseAtual == FASE_JUSTICA) && !pista3Encontrada;
                    } else if (objeto == OBJ_COMPUTADOR_DECISAO) {
                        objetoLinha = DECISAO_LINHA;
                        objetoColuna = DECISAO_COLUNA;
                        objetoLargura = 2;
                        objetoAtivo = (faseAtual == FASE_JUSTICA);
                    } else if (objeto == OBJ_COMPUTADOR_RESULTADOS) {
                        objetoLinha = RESULTADOS_LINHA;
                        objetoColuna = RESULTADOS_COLUNA;
                        objetoLargura = 2;
                        objetoAtivo = (faseAtual == FASE_JUSTICA);
                    } else {
                        objetoLinha = PORTA_FINAL_LINHA;
                        objetoColuna = PORTA_FINAL_COLUNA;
                        objetoAtivo = (faseAtual == FASE_SAIDA);
                    }

                    /* "perto" = em qualquer casa vizinha (inclui diagonais) */
                    pertoDoObjeto = jogadorLinha >= objetoLinha - 1 &&
                                    jogadorLinha <= objetoLinha + 1 &&
                                    jogadorColuna >= objetoColuna - 1 &&
                                    jogadorColuna <= objetoColuna + objetoLargura;

                    if (objetoProximo == OBJ_NENHUM && objetoAtivo && pertoDoObjeto) {
                        objetoProximo = objeto;
                    }
                }

                /* Reacao ao objeto encontrado, respeitando a ordem de cada fase */
                if (objetoProximo == OBJ_PISTA) {
                    pistaEncontrada = 1;
                    telaAtual = TELA_PISTA;
                } else if (objetoProximo == OBJ_COMPUTADOR1) {
                    if (pistaEncontrada) {
                        telaAtual = TELA_COMPUTADOR1;
                    } else {
                        mensagem = MSG_C1_BLOQUEADO;
                    }
                } else if (objetoProximo == OBJ_COMPUTADOR2) {
                    if (computador1Resolvido) {
                        telaAtual = TELA_COMPUTADOR2;
                    } else {
                        mensagem = MSG_C2_BLOQUEADO;
                    }
                } else if (objetoProximo == OBJ_PORTA) {
                    mensagem = MSG_PORTA_TRANCADA;
                } else if (objetoProximo == OBJ_CHAVE) {
                    chaveDaVerdade = 1;
                    telaAtual = TELA_CHAVE;
                } else if (objetoProximo == OBJ_ARQUIVO1) {
                    telaAtual = TELA_ARQUIVO;
                } else if (objetoProximo == OBJ_ARQUIVO2) {
                    telaRetorno = TELA_MAPA;            /* arquivo so com dados pessoais */
                    telaAtual = TELA_AVISO_PRIVACIDADE;
                } else if (objetoProximo == OBJ_COMPUTADOR_BLOQUEADO) {
                    if (codigoEncontrado) {
                        codigoDigitado = 0;
                        digitosDigitados = 0;
                        telaAtual = TELA_CODIGO;
                    } else {
                        mensagem = MSG_SISTEMA_BLOQUEADO;
                    }
                } else if (objetoProximo == OBJ_PISTA3) {
                    pista3Encontrada = 1;
                    telaAtual = TELA_PISTA3;
                } else if (objetoProximo == OBJ_COMPUTADOR_RESULTADOS) {
                    if (pista3Encontrada) {
                        resultadosVistos = 1;
                        telaAtual = TELA_RESULTADOS;
                    } else {
                        mensagem = MSG_RESULTADOS_BLOQUEADO;
                    }
                } else if (objetoProximo == OBJ_COMPUTADOR_DECISAO) {
                    if (resultadosVistos) {
                        telaAtual = TELA_DECISAO;
                    } else {
                        mensagem = MSG_DECISAO_BLOQUEADA;
                    }
                } else if (objetoProximo == OBJ_PORTA_FINAL) {
                    telaAtual = TELA_PORTA_FINAL;
                } else {
                    mensagem = MSG_NADA_PROXIMO;
                }

            } else if (tecla == 'I') {
                telaAtual = TELA_INVENTARIO;
            } else {                              /* Q */
                origemConfirmacao = TELA_MAPA;
                telaAtual = TELA_CONFIRMAR_SAIDA;
            }

        } else if (telaAtual == TELA_PISTA || telaAtual == TELA_PISTA3 ||
                   telaAtual == TELA_RESULTADOS) {
            telaAtual = TELA_MAPA;

        } else if (telaAtual == TELA_COMPUTADOR1) {
            /* Fase 1: julgar p (resposta F) e depois ~p (resposta V) */
            if (tecla == 'Q' || tecla == 'E') {
                telaAtual = TELA_MAPA;
            } else {
                respostaEsperada = (etapaComputador1 == 0) ? 'F' : 'V';
                if (tecla == respostaEsperada) {
                    etapaComputador1++;
                    mensagem = MSG_ACERTO;
                    if (etapaComputador1 == ETAPAS_C1) {
                        computador1Resolvido = 1;
                    }
                } else {
                    respostasIncorretas++;
                    mensagem = (etapaComputador1 == 0) ? MSG_ERRO_P : MSG_ERRO_NAO_P;
                }
            }

        } else if (telaAtual == TELA_COMPUTADOR2) {
            /* Fase 1: completar a tabela-verdade de p ^ q, uma linha por vez */
            if (tecla == 'Q' || tecla == 'E') {
                telaAtual = TELA_MAPA;
            } else {
                valorP = (linhaTabela < 2);
                valorQ = (linhaTabela % 2 == 0);
                respostaEsperada = (valorP && valorQ) ? 'V' : 'F';
                if (tecla == respostaEsperada) {
                    linhaTabela++;
                    mensagem = MSG_ACERTO;
                    if (linhaTabela == LINHAS_TABELA) {
                        computador2Resolvido = 1;
                        /* Regra da porta (conjuncao): abre se C1 E C2 corrigidos */
                        portaAberta = computador1Resolvido && computador2Resolvido;
                        mensagem = MSG_PORTA_ABERTA;
                    }
                } else {
                    respostasIncorretas++;
                    mensagem = MSG_ERRO_TABELA;
                }
            }

        } else if (telaAtual == TELA_ARQUIVO) {
            /* Fase 2: guardar apenas o dado necessario (codigo) */
            if (tecla == 'Q' || tecla == 'E') {
                telaAtual = TELA_MAPA;
            } else if (tecla == '1') {
                codigoEncontrado = 1;
                mensagem = MSG_CODIGO_GUARDADO;
            } else {                              /* 2: dados pessoais demais */
                respostasIncorretas++;
                telaRetorno = TELA_ARQUIVO;
                telaAtual = TELA_AVISO_PRIVACIDADE;
            }

        } else if (telaAtual == TELA_AVISO_PRIVACIDADE) {
            telaAtual = telaRetorno;              /* volta para onde estava */

        } else if (telaAtual == TELA_CODIGO) {
            /* Fase 2: cada digito entra no fim do numero (2 -> 20 -> 204 -> 2048) */
            if (tecla == 'Q') {
                telaAtual = TELA_MAPA;
            } else {
                codigoDigitado = codigoDigitado * 10 + (tecla - '0');
                digitosDigitados++;
                if (digitosDigitados == DIGITOS_CODIGO) {
                    if (codigoDigitado == CODIGO_ACESSO) {
                        chaveDaPrivacidade = 1;
                        telaAtual = TELA_CHAVE;
                    } else {
                        respostasIncorretas++;
                        mensagem = MSG_CODIGO_ERRADO;
                    }
                    codigoDigitado = 0;
                    digitosDigitados = 0;
                }
            }

        } else if (telaAtual == TELA_DECISAO) {
            /* Fase 3: remover o criterio inadequado (bairro) */
            if (tecla == 'Q') {
                telaAtual = TELA_MAPA;
            } else if (tecla == CRITERIO_INADEQUADO) {
                chaveDaJustica = 1;
                telaAtual = TELA_CHAVE;
            } else {
                respostasIncorretas++;
                mensagem = MSG_CRITERIO_LEGITIMO;
            }

        } else if (telaAtual == TELA_INVENTARIO) {
            telaAtual = TELA_MAPA;

        } else if (telaAtual == TELA_CHAVE) {
            /* Proxima fase: o jogador volta para a posicao inicial */
            faseAtual++;
            jogadorLinha = INICIO_LINHA;
            jogadorColuna = INICIO_COLUNA;
            destinoLinha = jogadorLinha;
            destinoColuna = jogadorColuna;
            telaAtual = TELA_MAPA;

        } else if (telaAtual == TELA_PORTA_FINAL) {
            telaAtual = (tecla == 'E') ? TELA_VITORIA : TELA_MAPA;

        } else if (telaAtual == TELA_VITORIA) {
            /* 1 = jogar novamente, 2 = menu, 3 = sair */
            if (tecla == '1') {
                reiniciarJogo = 1;
                telaAtual = TELA_MAPA;
            } else if (tecla == '2') {
                telaAtual = TELA_MENU;
            } else {
                telaAtual = TELA_ENCERRAR;
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
