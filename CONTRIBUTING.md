# Como contribuir com o NEXUS

Obrigado pelo interesse em ajudar! Este guia explica como configurar o ambiente e enviar uma contribuição para o NEXUS, um jogo educativo de aventura feito em C para rodar no terminal.

> 🪟 O NEXUS foi feito **apenas para Windows**, para rodar no **terminal integrado do VS Code**. Ele usa a biblioteca `conio.h`, que só existe no Windows.

## Sumário

- [Configurando o ambiente](#configurando-o-ambiente)
- [Compilando e executando](#compilando-e-executando)
- [Estrutura do repositório](#estrutura-do-repositório)
- [Como contribuir](#como-contribuir)
- [Padrão de código](#padrão-de-código)
- [Mensagens de commit](#mensagens-de-commit)
- [Testando antes de enviar](#testando-antes-de-enviar)
- [Reportando bugs e sugerindo melhorias](#reportando-bugs-e-sugerindo-melhorias)

---

## Configurando o ambiente

### 1. Instalar as ferramentas

- **Windows 10 ou 11.**
- **[VS Code](https://code.visualstudio.com/)**.
- **[Git](https://git-scm.com/downloads)**.
- **Compilador gcc (MinGW-w64)**. Uma forma simples de instalar é pelo [MSYS2](https://www.msys2.org/):
  1. Instale o MSYS2 e abra o terminal **MSYS2 UCRT64**.
  2. Rode: `pacman -S mingw-w64-ucrt-x86_64-gcc`
  3. Adicione a pasta `C:\msys64\ucrt64\bin` à variável de ambiente **Path** do Windows.

Para conferir, abra um terminal novo e digite:

```bash
gcc --version
git --version
```

Se as duas versões aparecerem, o ambiente está pronto.

### 2. Obter o código

Quem faz parte da equipe pode clonar o repositório direto:

```bash
git clone https://github.com/joaollima7/projeto-integrador-Nexus.git
cd projeto-integrador-Nexus
```

Quem **não** faz parte da equipe deve primeiro clicar em **Fork** no GitHub e clonar o seu fork (troque `SEU-USUARIO`):

```bash
git clone https://github.com/SEU-USUARIO/projeto-integrador-Nexus.git
cd projeto-integrador-Nexus
```

### 3. Abrir no VS Code

Abra a pasta com **Arquivo > Abrir Pasta...** e depois abra o terminal integrado com **Ctrl + '**.

---

## Compilando e executando

No terminal integrado, dentro da pasta do projeto:

```bash
gcc -Wall -Wextra -std=c99 nexus.c -o nexus.exe
.\nexus.exe
```

Dicas:

- Use o **terminal integrado** do VS Code. A aba *Output* não consegue ler as teclas do jogo.
- **Clique dentro do terminal** antes de jogar.
- Sempre compile de novo depois de mudar o código.
- O arquivo `nexus.c` precisa estar salvo em **UTF-8**, senão as molduras e os símbolos aparecem errados.

---

## Estrutura do repositório

| Arquivo | Para que serve |
|---|---|
| `nexus.c` | Código-fonte do jogo |
| `README.md` | Apresentação do projeto, instruções e documentação |
| `CONTRIBUTING.md` | Este guia |

O arquivo `nexus.exe` é gerado na compilação e **não deve ser enviado** para o repositório (ele é publicado nas *Releases*).

---

## Como contribuir

### Quem faz parte da equipe

A equipe trabalha direto na branch `main`. Para evitar conflitos:

1. Antes de começar, atualize o código:
   ```bash
   git pull
   ```
2. Faça uma mudança pequena e focada.
3. Compile e teste (veja [Testando antes de enviar](#testando-antes-de-enviar)).
4. Faça o commit e envie:
   ```bash
   git add nexus.c
   git commit -m "Corrige a colisão do personagem com a parede"
   git push
   ```
5. Se o `git push` for recusado, rode `git pull` de novo, resolva o que for preciso e tente outra vez.

