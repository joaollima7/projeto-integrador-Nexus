<p align="center"><img width="1316" height="912" alt="image" src="https://github.com/user-attachments/assets/6096c153-6d2b-47fe-a0ac-a42d895e7dbc" />

## 📑 Sumário

- [📖 Sobre o jogo](#-sobre-o-jogo)
- [🎯 Objetivo](#-objetivo)
- [⭐ Principais características](#-principais-características)
- [🕹️ Controles](#️-controles)
- [🗺️ Como funciona a aventura](#️-como-funciona-a-aventura)
- [🧩 Sistema de jogo](#-sistema-de-jogo)
- [🛠️ Tecnologias](#️-tecnologias)
- [📥 Baixar e jogar](#-baixar-e-jogar)
- [▶️ Como compilar e executar no VS Code](#️-como-compilar-e-executar-no-vs-code)
- [🤝 Como contribuir](#-como-contribuir)
- [📚 Documentação de FDS](#-documentação-de-fds)
- [👥 Integrantes](#-integrantes)
- [🚀 Proposta do projeto](#-proposta-do-projeto)
- [📎 Anexos](#-anexos)

---

## 📖 Sobre o jogo

**NEXUS** é um jogo educativo de aventura e exploração desenvolvido para ser executado diretamente no terminal, com um visual colorido.

O jogador fica preso dentro de um sistema controlado por uma Inteligência Artificial chamada **NEXUS**. Para conseguir escapar, será necessário explorar os mapas, encontrar pistas, investigar computadores, resolver problemas e coletar três chaves de segurança.

Durante a aventura, o jogador entra em contato com conceitos importantes relacionados ao uso da Inteligência Artificial, como:

- 🧠 Informações falsas e alucinações;
- 🔐 Privacidade e proteção de dados;
- ⚖️ Viés e decisões injustas;
- 🤖 Decisões automatizadas.

A proposta é transformar esses assuntos em uma experiência simples e interativa, utilizando exploração e resolução de situações dentro do próprio jogo.

---

## 🎯 Objetivo

O objetivo principal é conseguir as três chaves de segurança:

- 🔑 Chave da Verdade
- 🔑 Chave da Privacidade
- 🔑 Chave da Justiça

Depois de conseguir todas elas, o jogador precisa chegar até a porta de saída para escapar do sistema NEXUS.

---

## ⭐ Principais características

- 🎮 Aventura e exploração em modo terminal, com cores e molduras para deixar a tela mais bonita;
- 🗺️ Mapas diferentes em cada fase;
- 🚶 Movimentação pelo mapa;
- 🔎 Exploração e descoberta de pistas;
- 💻 Interação com computadores e arquivos;
- 🔑 Sistema de itens e chaves;
- 💬 Retorno imediato a cada resposta (acerto ou erro), com explicação do erro;
- 📋 Resumo de desempenho ao final da aventura;
- 🧠 Conteúdo educativo sobre Inteligência Artificial;
- 🏆 Fase final com objetivo de escapar do sistema.

---

## 🕹️ Controles

O jogo utiliza comandos simples para facilitar a navegação. **Não é preciso apertar ENTER:** o jogo reage assim que você aperta a tecla. Letras maiúsculas e minúsculas funcionam.

| Tecla | Função |
|:---:|---|
| `W` | Mover para cima |
| `S` | Mover para baixo |
| `A` | Mover para a esquerda |
| `D` | Mover para a direita |
| `E` | Interagir com objetos, computadores e arquivos (quando estiver ao lado deles) |
| `I` | Abrir o inventário |
| `Q` | Sair (pede confirmação; ao voltar ao menu, o progresso é perdido) |

> As setas do teclado não são usadas: o movimento é feito apenas com `W`, `A`, `S` e `D`. Teclas que não servem para a tela atual são ignoradas e o jogo avisa, sem travar.

**Símbolos do mapa:**

| Símbolo | Significado |
|:---:|---|
| `●` | Jogador |
| `██` | Parede |
| `·` | Chão |
| `?` | Pista |
| `C` | Computador |
| `A` | Arquivo |
| `D` | Porta |
| `/` | Porta aberta |
| `K` | Chave |

> 💡 **Dica:** explore o mapa com atenção. Algumas informações importantes estão espalhadas pelo cenário.

---

## 🗺️ Como funciona a aventura

A aventura é dividida em três fases principais e uma etapa final.

### 🧠 Fase 1 — Central da Verdade

O sistema NEXUS apresenta informações incorretas nos computadores da sala.

O jogador deve:

1. Explorar a sala e encontrar a pista;
2. Investigar o computador C1 e julgar se as afirmações da IA são verdadeiras ou falsas;
3. Corrigir o filtro de confiança do computador C2, completando uma tabela-verdade;
4. Abrir a porta, que só destranca depois que C1 e C2 estiverem corrigidos;
5. Coletar a Chave da Verdade.

**Tema:** informações falsas e confiabilidade das informações geradas por IA, com noções de lógica (verdadeiro e falso, negação e conjunção).

### 🔐 Fase 2 — Setor de Privacidade

O sistema está armazenando informações pessoais que não são necessárias para realizar suas tarefas.

O jogador deve:

1. Explorar o setor e examinar os arquivos;
2. Guardar apenas o dado necessário para a missão, sem coletar dados pessoais;
3. Digitar o código de acesso no computador bloqueado;
4. Coletar a Chave da Privacidade.

**Tema:** privacidade e uso responsável de dados.

### ⚖️ Fase 3 — Núcleo da Justiça

O sistema de decisões da NEXUS está utilizando uma informação inadequada para tomar uma decisão.

O jogador deve:

1. Encontrar uma pista;
2. Ver os resultados da IA no computador C2;
3. Analisar os critérios usados pela IA no computador C1 e identificar o inadequado;
4. Corrigir o sistema de decisão;
5. Coletar a Chave da Justiça.

**Tema:** viés e decisões automatizadas.

### 🚪 Fase Final — Escape

Depois de conseguir as três chaves, o jogador finalmente pode chegar à porta de saída.

```
[ Chave da Verdade ]       ✓
[ Chave da Privacidade ]   ✓
[ Chave da Justiça ]       ✓

          ↓

      PORTA FINAL

          ↓

       ESCAPE!
```

Se todas as chaves tiverem sido encontradas, a porta é desbloqueada e o jogador consegue escapar do sistema.

---

## 🧩 Sistema de jogo

O NEXUS foi pensado para utilizar mecânicas simples e reaproveitáveis.

### 🔎 Exploração

O jogador percorre os mapas procurando objetos, pistas e computadores. Paredes e objetos bloqueiam a passagem: o personagem não atravessa obstáculos.

### 💻 Interação

Ao chegar perto de um objeto importante, o jogador pode utilizar a tecla `E` para interagir com ele. Os objetos seguem uma ordem em cada fase: por exemplo, o computador C2 só é liberado depois que o C1 for corrigido.

### 🎒 Inventário

As chaves e outros itens encontrados ficam registrados no inventário do jogador.

### 📋 Desempenho

Ao escapar, o jogo mostra quantas respostas incorretas o jogador deu durante a aventura e uma avaliação do desempenho (perfeito, muito bom ou continue praticando). Em seguida, é possível jogar novamente, voltar ao menu ou sair.

---

## 🛠️ Tecnologias

- **C** — desenvolvimento de todo o jogo: menus, movimentação, mapas, regras e fluxo das fases;
- **Terminal** — interface principal da experiência, usando cores (códigos ANSI) e caracteres Unicode (molduras e blocos) para o visual.

> 🪟 **Plataforma:** o jogo foi feito apenas para **Windows**, para ser executado no **terminal do VS Code**. Ele usa a biblioteca `conio.h`, que só existe no Windows, para ler as teclas sem precisar apertar ENTER.

---

## 📥 Baixar e jogar

Não quer compilar? Baixe o jogo pronto na **Release** do projeto:

🔗 **https://github.com/joaollima7/projeto-integrador-Nexus/releases/latest**

1. Abra o link e baixe o arquivo `nexus.exe`, na parte **Assets**;
2. Abra o terminal do VS Code (ou o Prompt de Comando) na pasta onde o arquivo foi salvo;
3. Execute `.\nexus.exe` (no Prompt de Comando, `nexus.exe`).

> 🪟 Só funciona no Windows. O Windows pode mostrar um aviso de segurança, porque o arquivo não é assinado: clique em **Mais informações → Executar assim mesmo**.

---

## ▶️ Como compilar e executar no VS Code

### Pré-requisitos

- Windows 10 ou 11;
- [VS Code](https://code.visualstudio.com/) instalado;
- Compilador **gcc** (MinGW-w64) instalado e disponível no terminal. Para conferir, abra um terminal e digite `gcc --version`: se aparecer a versão, está tudo certo.

### 1. Abrir o projeto no VS Code

Clone o repositório:

```bash
git clone https://github.com/joaollima7/projeto-integrador-Nexus.git
```

No VS Code, vá em **Arquivo > Abrir Pasta...** (File > Open Folder...) e selecione a pasta do repositório.

### 2. Abrir o terminal integrado

Vá em **Terminal > Novo Terminal** (Terminal > New Terminal) ou use o atalho **Ctrl + '**. O terminal abre na parte de baixo da janela, já dentro da pasta do projeto.

### 3. Compilar

No terminal, digite:

```bash
gcc -Wall -Wextra -std=c99 nexus.c -o nexus.exe
```

O código compila **sem erros e sem avisos (warnings)**, mesmo com as opções `-Wall -Wextra`. Depois da compilação, o arquivo `nexus.exe` aparece na pasta do projeto.

### 4. Executar

No mesmo terminal, digite:

```bash
.\nexus.exe
```

(Se o terminal for o Prompt de Comando, use `nexus.exe`, sem o `.\`.)

> 💡 **Dicas:**
> - Use o **terminal integrado** (passo 2) para executar o jogo. A aba *Output* (usada por extensões como o botão "Run Code") não consegue ler as teclas do jogo.
> - **Clique dentro do terminal** antes de começar a jogar, para que as teclas sejam enviadas ao jogo.
> - Para ver a tela inteira sem rolagem, aumente a área do terminal arrastando a borda dele para cima.
> - O jogo muda sozinho o terminal para UTF-8 e liga as cores. Se as molduras e os símbolos aparecerem estranhos, confira se o arquivo `nexus.c` está salvo em **UTF-8** (aparece no canto inferior direito do VS Code) e recompile.
> - Sempre que mudar o código, compile de novo antes de executar.

---

## 🤝 Como contribuir

Quer ajudar no projeto? Veja o guia [CONTRIBUTING.md](CONTRIBUTING.md), que explica como configurar o ambiente, compilar o jogo e enviar uma contribuição.

---

## 📚 Documentação de FDS

> 📌 Os itens desta seção fazem parte das entregas da disciplina de **FDS (Fundamentos de Desenvolvimento de Software)**.

### Histórias de usuário

Todas as histórias de usuário planejadas foram implementadas no jogo.

| ID | História de usuário | Implementada |
|:---:|---|:---:|
| US01 | Como jogador, quero iniciar um novo jogo pelo menu, para começar minha aventura no sistema NEXUS. | ✅ |
| US02 | Como jogador, quero visualizar as instruções, para entender os comandos do jogo. | ✅ |
| US03 | Como jogador, quero movimentar meu personagem pelo mapa, para explorar as fases do jogo. | ✅ |
| US04 | Como jogador, quero interagir com objetos do mapa, para encontrar pistas e avançar nas fases. | ✅ |
| US05 | Como jogador, quero encontrar pistas na primeira fase, para descobrir qual informação da IA não é confiável. | ✅ |
| US06 | Como jogador, quero investigar os computadores da primeira fase, para identificar o sistema que apresenta erro. | ✅ |
| US07 | Como jogador, quero corrigir o computador com erro, para resolver o problema da primeira fase. | ✅ |
| US08 | Como jogador, quero encontrar arquivos na segunda fase, para descobrir informações necessárias para continuar. | ✅ |
| US09 | Como jogador, quero evitar o uso de dados pessoais desnecessários, para aprender sobre privacidade no uso da IA. | ✅ |
| US10 | Como jogador, quero encontrar o código de acesso, para desbloquear o sistema da segunda fase. | ✅ |
| US11 | Como jogador, quero corrigir o problema de privacidade, para receber a Chave da Privacidade. | ✅ |
| US12 | Como jogador, quero encontrar uma pista sobre uma decisão injusta na terceira fase, para identificar um problema no sistema de IA. | ✅ |
| US13 | Como jogador, quero investigar os computadores da terceira fase, para encontrar o erro na decisão da IA. | ✅ |
| US14 | Como jogador, quero corrigir o sistema da terceira fase, para resolver o problema de decisão injusta. | ✅ |
| US15 | Como jogador, quero usar as três chaves para abrir a saída, para conseguir escapar do sistema NEXUS. | ✅ |

### Evolução do jogo

O NEXUS foi crescendo por etapas, sempre com uma versão que podia ser jogada:

1. **Planejamento:** a equipe definiu a ideia do jogo, organizou as tarefas no Jira e desenhou o fluxo de telas (protótipo no Figma) e o diagrama de atividades.
2. **Primeira versão:** o jogo começou simples, com o menu inicial, a tela de instruções e um mapa em que o personagem se movia com `W`, `A`, `S` e `D`.
3. **Interação:** foram incluídas as paredes que bloqueiam a passagem, a tecla `E` para interagir com objetos próximos e o inventário.
4. **Fase 1:** surgiram a pista, os computadores com as afirmações da IA e a tabela-verdade, a porta que só abre quando o sistema é corrigido e a primeira chave.
5. **Fases 2 e 3:** foram criados os arquivos e o código de acesso da fase de privacidade e, depois, os computadores da fase de justiça, cada uma com seu mapa e sua chave.
6. **Fase final:** a porta de saída passou a exigir as três chaves e foi criada a tela de vitória, com o resumo de desempenho e a opção de jogar novamente.
7. **Acabamento:** o visual do terminal ganhou cores e molduras, as teclas passaram a ser validadas para o jogo não travar com entradas erradas, e a equipe fez testes e correções de bugs.
8. **Hoje:** o jogo está completo e jogável do menu até o escape, no terminal do VS Code, no Windows.

### Issues e bug tracker

Os bugs encontrados durante o desenvolvimento e as histórias de usuário foram registrados como issues no GitHub, com labels e marco da versão `v1.0.0`. Todos já foram resolvidos e fechados.

🔗 [Ver as issues do projeto](https://github.com/joaollima7/projeto-integrador-Nexus/issues?q=is%3Aissue)

<!-- Cole aqui o print das issues -->

### Screencast (FDS) - Entrega 3

https://drive.google.com/file/d/1eNFy9aUQpbELpfwjV-a6egrFYfncJwG8/view?usp=drivesdk

### Screencast (FDS) - Entrega 4

https://drive.google.com/file/d/1XeyO1ZS0Zp9XKz_Lj7U1RG53p1rWexsV/view?usp=sharing

---

## 👥 Integrantes

| Integrante | Função |
|---|---|
| Rodrigo Alves | Desenvolvimento principal em C e integração do jogo |
| João Victor Queiroz ([@jvqmg](https://github.com/jvqmg)) | Desenvolvimento dos mapas e movimentação |
| João Victor Nicacio | Sistema de interação e itens |
| João Guilherme Queiroz ([@joaoguilhermeqmg](https://github.com/joaoguilhermeqmg)) | Desenvolvimento das fases e missões |
| Danilo Barros | Regras do jogo |
| Gustavo Cassemiro | Testes e correção de erros |
| Daniel Luiz | Apoio no desenvolvimento do jogo |
| Fernando Araújo | Apoio no desenvolvimento e organização do projeto |
| Lucas Collier ([@LucasCollier](https://github.com/LucasCollier)) | Modularização do código e correção de bugs |

---

## 🚀 Proposta do projeto

O NEXUS busca unir programação e aprendizado sobre Inteligência Artificial em uma experiência simples de jogar e desenvolver.

Em vez de apresentar os conceitos apenas como perguntas, o jogador aprende enquanto explora, investiga e resolve problemas dentro do sistema.

A missão é simples: encontrar as três chaves, corrigir os erros do sistema e escapar.

<p align="center">
  <b>🎮 NEXUS</b><br>
  <i>Explore o sistema. Descubra os erros. Recupere as chaves.<br>
  Escape do NEXUS</i>
</p>

---

## 📎 Anexos

- **Link do Trello:** https://trello.com/invite/b/6a99efa1bc0ba7766566dcf9/ATTI9fdd42898827a53c75effbdee9083b71BA91C41C/projeto-integrador-entregas-fds
- **Link do Protótipo Navegável Lo-Fi:** https://www.figma.com/design/KaKeypsS67eQHAWmZoUpev/NEXUS-—-Fluxo-de-Telas?node-id=0-1&t=RsjCwZyaYFWcjrjL-1
- **Link do Diagrama de Atividades:** https://www.figma.com/board/ECGOhLU5rYH2vMqNarHMec/Diagramas-de-atividades---FDS?node-id=0-1&t=GH0cTbkJmIx6VAhe-1
