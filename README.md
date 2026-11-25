<p align="center"><img src="<img width="1316" height="912" alt="image" src="https://github.com/user-attachments/assets/6c97d4b5-467a-42c1-9a7b-d209ffa4ecb2" />
" alt="NEXUS" width="640"></p>

## 📑 Sumário

- [📖 Sobre o jogo](#-sobre-o-jogo)
- [🎯 Objetivo](#-objetivo)
- [⭐ Principais características](#-principais-características)
- [🕹️ Controles](#️-controles)
- [🗺️ Como funciona a aventura](#️-como-funciona-a-aventura)
- [🧩 Sistema de jogo](#-sistema-de-jogo)
- [🛠️ Tecnologias](#️-tecnologias)
- [▶️ Como compilar e executar no VS Code](#️-como-compilar-e-executar-no-vs-code)
- [📚 Documentação de FDS](#-documentação-de-fds)
- [👥 Integrantes](#-integrantes)
- [🚀 Proposta do projeto](#-proposta-do-projeto)
- [📎 Anexos](#-anexos)

---

## 📖 Sobre o jogo

*NEXUS* é um jogo educativo de aventura e exploração desenvolvido para ser executado diretamente no terminal.

O jogador fica preso dentro de um sistema controlado por uma Inteligência Artificial chamada *NEXUS*. Para conseguir escapar, será necessário explorar os mapas, encontrar pistas, investigar computadores, resolver problemas e coletar três chaves de segurança.

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

- 🎮 Aventura e exploração em modo terminal;
- 🗺️ Mapas diferentes em cada fase;
- 🚶 Movimentação pelo mapa;
- 🔎 Exploração e descoberta de pistas;
- 💻 Interação com computadores e objetos;
- 🔑 Sistema de itens e chaves;
- 💾 Salvamento do progresso;
- 🧠 Conteúdo educativo sobre Inteligência Artificial;
- 🏆 Fase final com objetivo de escapar do sistema.

---

## 🕹️ Controles

O jogo utiliza comandos simples para facilitar a navegação. *Não é preciso apertar ENTER:* o jogo reage assim que você aperta a tecla. Letras maiúsculas e minúsculas funcionam.

| Tecla | Função |
|:---:|---|
| W | Mover para cima |
| S | Mover para baixo |
| A | Mover para a esquerda |
| D | Mover para a direita |
| E | Interagir com objetos e computadores (ao lado do jogador) |
| I | Abrir o inventário |
| P | Salvar o jogo (o salvamento em arquivo será implementado em uma próxima etapa) |
| Q | Sair do jogo (pede confirmação) |

*Símbolos do mapa:*

| Símbolo | Significado |
|:---:|---|
| P | Jogador |
| # | Parede |
| . | Chão |
| ? | Pista |
| C | Computador |
| D | Porta |
| / | Porta aberta |
| K | Chave |

> 💡 *Dica:* explore o mapa com atenção. Algumas informações importantes estão espalhadas pelo cenário.

---

## 🗺️ Como funciona a aventura

A aventura é dividida em três fases principais e uma etapa final.

### 🧠 Fase 1 — Central da Verdade

O sistema NEXUS apresenta informações incorretas em um de seus computadores.

O jogador deve:

1. Explorar o mapa;
2. Encontrar uma pista;
3. Investigar os computadores;
4. Descobrir qual deles apresenta o erro;
5. Corrigir o sistema;
6. Coletar a Chave da Verdade.

*Tema:* informações falsas e confiabilidade das informações geradas por IA.

### 🔐 Fase 2 — Setor de Privacidade

O sistema está armazenando informações pessoais que não são necessárias para realizar suas tarefas.

O jogador deve explorar o setor, encontrar os arquivos necessários e descobrir um código para desbloquear o sistema.

Ao concluir a missão, recebe a Chave da Privacidade.

*Tema:* privacidade e uso responsável de dados.

### ⚖️ Fase 3 — Núcleo da Justiça

O sistema de decisões da NEXUS está utilizando uma informação inadequada para tomar uma decisão.

O jogador deve:

1. Encontrar uma pista;
2. Investigar os computadores;
3. Identificar a informação que está causando o problema;
4. Corrigir o sistema;
5. Coletar a Chave da Justiça.

*Tema:* viés e decisões automatizadas.

### 🚪 Fase Final — Escape

Depois de conseguir as três chaves, o jogador finalmente pode chegar à porta de saída.


[ Chave da Verdade ]       ✓
[ Chave da Privacidade ]   ✓
[ Chave da Justiça ]       ✓

          ↓

      PORTA FINAL

          ↓

       ESCAPE!


Se todas as chaves tiverem sido encontradas, a porta é desbloqueada e o jogador consegue escapar do sistema.

---

## 🧩 Sistema de jogo

O NEXUS foi pensado para utilizar mecânicas simples e reaproveitáveis.

### 🔎 Exploração

O jogador percorre os mapas procurando objetos, pistas e computadores. Paredes e objetos bloqueiam a passagem: o personagem não atravessa obstáculos.

### 💻 Interação

Ao encontrar um objeto importante, o jogador pode utilizar a tecla E para interagir com ele.

### 🎒 Inventário

As chaves e outros itens encontrados ficam registrados no inventário do jogador.

### 💾 Salvamento

O progresso pode ser salvo para que o jogador continue a aventura posteriormente.

---

## 🛠️ Tecnologias

- *C* — desenvolvimento principal do jogo, menus, movimentação, mapas e fluxo das fases;
- *Arquivos* — armazenamento do progresso e informações do jogo;
- *Terminal* — interface principal da experiência.

> 🪟 *Plataforma:* o jogo foi feito apenas para *Windows*. Ele usa a biblioteca conio.h, que só existe no Windows, para ler as teclas sem precisar apertar ENTER.

---

## ▶️ Como compilar e executar no VS Code

### 1. Abrir o projeto no VS Code

Clone o repositório:

bash
git clone <https://github.com/joaollima7/projeto-integrador-Nexus.git>


No VS Code, vá em *Arquivo > Abrir Pasta...* (File > Open Folder...) e selecione a pasta do repositório.

### 2. Abrir o terminal integrado

Vá em *Terminal > Novo Terminal* (Terminal > New Terminal) ou use o atalho *Ctrl + '*. O terminal abre na parte de baixo da janela, já dentro da pasta do projeto.

### 3. Compilar

No terminal, digite:

bash
gcc -Wall -Wextra -std=c99 nexus.c -o nexus.exe


O código compila *sem erros e sem avisos (warnings)*, mesmo com as opções -Wall -Wextra. Depois da compilação, o arquivo nexus.exe aparece na pasta do projeto.

### 4. Executar

No mesmo terminal, digite:

bash
.\nexus.exe


> 💡 *Dicas:*
> - Use o *terminal integrado* (passo 2) para executar o jogo. A aba Output (usada por extensões como o botão "Run Code") não consegue ler as teclas do jogo.
> - *Clique dentro do terminal* antes de começar a jogar, para que as teclas sejam enviadas ao jogo.
> - Para ver melhor o mapa, aumente a área do terminal arrastando a borda dele para cima.

---

## 📚 Documentação de FDS

> 📌 Os itens desta seção fazem parte das entregas da disciplina de *FDS (Fundamentos de Desenvolvimento de Software)*.

### Screencast (FDS):

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
| Danilo Barros | Sistema de pontuação e regras |
| Gustavo Cassemiro | Testes e correção de erros |
| Daniel Luiz | Sistema de salvamento e arquivos |
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

- *Link do Trello:* https://trello.com/invite/b/6a99efa1bc0ba7766566dcf9/ATTI9fdd42898827a53c75effbdee9083b71BA91C41C/projeto-integrador-entregas-fds
- *Link do Protótipo Navegável Lo-Fi:* https://www.figma.com/design/KaKeypsS67eQHAWmZoUpev/NEXUS-—-Fluxo-de-Telas?node-id=0-1&t=RsjCwZyaYFWcjrjL-1
- *Link do Diagrama de Atividades:* https://www.figma.com/board/ECGOhLU5rYH2vMqNarHMec/Diagramas-de-atividades---FDS?node-id=0-1&t=GH0cTbkJmIx6VAhe-1
