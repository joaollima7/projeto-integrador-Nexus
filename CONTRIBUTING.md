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

### Quem está de fora (Pull Request)

1. Faça o fork e clone o seu fork.
2. Crie uma branch com um nome que explique a mudança:
   ```bash
   git checkout -b corrige-colisao-parede
   ```
3. Faça as mudanças, compile e teste.
4. Faça o commit e envie a branch:
   ```bash
   git add nexus.c
   git commit -m "Corrige a colisão do personagem com a parede"
   git push origin corrige-colisao-parede
   ```
5. No GitHub, abra um **Pull Request** para a `main` do repositório original. Explique o que mudou, por quê e como testar. Se o PR resolver uma issue, escreva `Closes #número` na descrição.

---

## Padrão de código

- **Linguagem:** C no padrão C99.
- **Sem avisos:** o código deve compilar sem erros e **sem warnings** com `-Wall -Wextra -std=c99`.
- **Nomes claros:** variáveis, funções e constantes com nomes que expliquem o que são (`jogadorLinha`, `chaveDaVerdade`). Evite nomes como `x`, `a` ou `aux`.
- **Comentários:** explique a finalidade dos blocos principais. Comente o porquê, não o óbvio.
- **Sem repetir código:** se um bloco aparece mais de uma vez, reaproveite.
- **Constantes:** use `#define` para números e textos fixos, em vez de números soltos no meio do código.
- **Plataforma:** mantenha o jogo funcionando no Windows e no terminal do VS Code.
- **Validação:** teclas inválidas devem ser ignoradas com aviso. O jogo nunca pode travar nem fechar de forma inesperada.
- **Sem conteúdo extra:** não inclua arquivos compilados (`.exe`) nem arquivos pessoais do editor.

---

## Mensagens de commit

Use uma frase curta, no imperativo, dizendo **o que** a mudança faz:

| Bom | Ruim |
|---|---|
| `Corrige a porta que abria sem a chave` | `arrumei coisa` |
| `Adiciona o inventário na tela do mapa` | `update` |
| `Atualiza o README com as instruções` | `mudanças` |

Se precisar explicar mais, escreva uma segunda linha de descrição (`git commit -m "título" -m "descrição"`).

---

## Testando antes de enviar

O projeto não tem testes automáticos, então teste jogando. Antes de enviar, confira:

- [ ] O código compila sem erros e sem warnings.
- [ ] O menu funciona (`1` inicia, `2` mostra as instruções, `3` sai).
- [ ] O personagem se move com `W`, `A`, `S`, `D` sem precisar de ENTER e para na parede com aviso.
- [ ] A tecla `E` interage com o objeto ao lado e `I` abre o inventário.
- [ ] Teclas inválidas mostram aviso e o jogo não trava.
- [ ] A parte que você mudou funciona do início ao fim.
- [ ] Se mexeu em uma fase, jogue a fase inteira até pegar a chave.
- [ ] Se mexeu no fluxo final, jogue até a tela de vitória e teste "jogar novamente" e "sair".

---

## Reportando bugs e sugerindo melhorias

Abra uma [issue](https://github.com/joaollima7/projeto-integrador-Nexus/issues/new) e inclua:

**Para um bug:**
- o que aconteceu e o que era esperado;
- os passos para reproduzir (em qual fase, quais teclas);
- uma imagem do terminal, se ajudar;
- o seu Windows e a versão do gcc (`gcc --version`).

**Para uma sugestão:**
- o que você gostaria de ver no jogo e por que isso melhora a experiência.

Antes de abrir, procure nas issues se alguém já reportou o mesmo assunto.
