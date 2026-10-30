# Fila Zero — app da cantina do CESAR

Projeto do Hackathon Relâmpago #1 de FDS 2026.2 (Prof. Lucas Farias), sobre os princípios de projeto do capítulo 5 do livro do Marco Tulio Valente.

## A ideia

Todo mundo aqui já perdeu metade do intervalo na fila da cantina e engoliu o lanche no tempo que sobrou. A gente quis resolver isso com algo simples: o aluno pede **ainda na aula**, paga, vê quanto tempo vai demorar e recebe um aviso quando o pedido fica pronto. No intervalo, só passa no balcão e pega.

O que o app faz hoje:

- mostra o cardápio do dia (com um combo);
- recebe o pedido antecipado;
- cobra por Pix ou cartão;
- aplica desconto (tem duas regras de exemplo);
- estima o tempo de espera de acordo com a fila;
- avisa o aluno quando o pedido está pronto.

É uma prova de conceito, então roda no terminal, não tem banco de dados (tudo fica em memória) e os pagamentos são simulados. Nosso foco foi a organização do código, não a tela.

## Quem fez o quê

- **João Victor Lima:** desenhou a arquitetura e cuidou do núcleo do domínio (`interfaces.py`, `models.py` e `servico.py`).
- **João Guilherme:** ficou com pagamentos, descontos e avisos (`pagamentos.py`, `descontos.py` e `notificadores.py`).
- **Rodrigo Alves:** fez o cardápio, os combos e a fila com a estimativa de espera (`cardapio.py` e `fila.py`).
- **Danilo Barros:** escreveu os testes, a demo (`main.py`), este README e gravou o vídeo.

## Por que essa stack

- **Python 3**, porque dá para prototipar rápido e o código fica fácil de ler na hora de explicar.
- **Sem bibliotecas externas.** Só a biblioteca padrão, então ninguém precisa instalar nada para rodar.
- **Terminal** como interface, para não gastar a aula com tela e focar no projeto.
- **unittest** para os testes, que já vem com o Python.
- **IA** ajudou a escrever o código (a atividade liberou), mas as decisões de projeto e as explicações são nossas.

## Como rodar

Precisa do Python 3.10 ou mais novo.

```bash
git clone <URL-DO-REPOSITORIO>
cd cantina-cesar

python main.py                 # roda a demo com dois alunos fazendo pedido
python -m unittest discover    # roda os testes
```

## Onde estão os princípios do capítulo 5

Aqui está o que a gente aplicou de verdade, onde achar no código e por que melhorou o projeto.

**Responsabilidade Única.** Cada classe tem um motivo só para mudar. O `Cardapio` só sabe o que a cantina vende, a `FilaCantina` só cuida da ordem e da estimativa de espera, e cada forma de pagamento só cobra. Ficou fácil mexer em uma parte sem quebrar as outras. (`cardapio.py`, `fila.py`, `pagamentos.py`)

**Ocultamento de Informação.** No `Pedido` (`models.py`), a lista de itens e o status são privados. Quem quiser mudar algo tem que passar por `adicionar()`, `confirmar()` ou `marcar_pronto()`. Com isso dá para garantir uma regra: depois de confirmado, o pedido não pode mais ser alterado.

**Inversão de Dependências.** O `ServicoPedidos` (`servico.py`) não sabe se o pagamento é Pix ou cartão, nem como o aluno é avisado. Ele recebe tudo pelo construtor, como abstrações definidas em `interfaces.py`. Quem escolhe as implementações concretas é o `main.py`, e trocar uma delas é mudar uma linha.

**Segregação de Interfaces.** Em vez de uma interface gigante, são três pequenas com um método cada: `Notificador`, `MeioPagamento` e `Desconto`. Nenhuma classe é obrigada a implementar o que não usa.

**Aberto/Fechado.** Em `descontos.py`, o `DescontoTresOuMais` foi adicionado depois como uma classe nova, sem mexer no serviço nem nos outros descontos. Para criar uma regra nova, é só escrever outra classe.

**Substituição de Liskov.** `PagamentoPix` e `PagamentoCartao` seguem o mesmo contrato (`pagar(valor)` devolve `True` ou `False`), então um entra no lugar do outro sem o serviço perceber. Tem um teste só para isso.

**Composição em vez de herança.** O `Combo` (`models.py`) *tem* itens, não *é* um item. O preço e o tempo de preparo dele são calculados a partir dos itens que o compõem.

**Lei de Demeter.** O `ServicoPedidos` conversa só com o `Pedido` (`subtotal()`, `qtd_itens()`) e não fica abrindo o pedido para mexer nos itens por dentro.

**Coesão, acoplamento e integridade conceitual.** Os módulos são pequenos, cada um sobre um assunto só, e se ligam por interfaces. O vocabulário (Pedido, Cardápio, Fila) e o jeito de injetar dependências são os mesmos em todo o projeto.

## Estrutura das pastas

```
cantina-cesar/
├── main.py                  # monta tudo e roda a demo
├── cantina/
│   ├── interfaces.py        # Notificador, MeioPagamento, Desconto
│   ├── models.py            # ItemCardapio, Combo, Pedido, Status
│   ├── cardapio.py
│   ├── descontos.py
│   ├── pagamentos.py
│   ├── notificadores.py
│   ├── fila.py
│   └── servico.py
└── tests/test_principios.py
```

## Vídeo

Link do vídeo (até 3 minutos): **COLE AQUI**

## Sobre as entregas

Esta é a Entrega 1, a versão "go-horse" feita em sala. O repositório não vai mais ser editado depois da aula de 29/10. A PoC final vai em outro repositório, até 04/11.
