# Controle de LED e Matriz de LEDs com Botões de Incremento/Decremento

Este projeto utiliza um microcontrolador Raspberry Pi Pico e é responsável por controlar um LED indicador e uma matriz de LEDs 5x5. O programa permite incrementar ou decrementar um número exibido na matriz de LEDs utilizando dois botões, um para incremento e outro para decremento. O número exibido é atualizado na matriz de LEDs e é controlado com debounce para evitar leituras errôneas.

## Requisitos

- Raspberry Pi Pico ou microcontrolador compatível com a biblioteca `pico/stdlib`.
- Matriz de LEDs 5x5 (ou matriz de LEDs com 25 pixels).

## Componentes

  - **LED indicador**: Um LED que alterna seu estado a cada intervalo.
  - **Botões**: Dois botões são usados para controlar o número exibido na matriz de LEDs:
  - **Botão de incremento (BUTTON_UP)**: Aumenta o número exibido.
  - **Botão de decremento (BUTTON_DOWN)**: Diminui o número exibido.

## Funcionalidades

- **Incrementar/Decrementar número**: A matriz de LEDs exibe números de 0 a 9, e a cada pressionamento dos botões de incremento ou decremento, o número é atualizado.
- **Debounce**: O sistema implementa uma técnica de debounce para evitar múltiplas leituras indesejadas ao pressionar o botão.
- **Controle de LED**: O LED indicador alterna seu estado periodicamente a cada intervalo definido.

## Estrutura do Código

### 1. Manipuladores de Interrupção

O código define uma função `button_irq_handler` que é chamada sempre que um dos botões é pressionado. Ela verifica qual botão foi pressionado, atualiza o número exibido na matriz de LEDs e implementa a lógica de debounce para garantir que o número não seja alterado repetidamente de forma errada.

### 2. Configuração da Matriz de LEDs

A função `setup_matrix` inicializa a matriz de LEDs, que é controlada por um PIO (Programmable I/O) do Raspberry Pi Pico. A matriz exibe números de 0 a 9 de acordo com a seleção feita pelo usuário.

### 3. Função Principal

A função principal do programa inicializa os periféricos (matriz de LEDs, LED indicador e botões), configura as interrupções para os botões e entra em um loop que alterna o estado do LED indicador e aguarda o acionamento dos botões.

## Como Utilizar

### 1. Compilação e Execução

O código pode ser compilado e carregado no Raspberry Pi Pico utilizando uma ferramenta como o `make` ou diretamente via ambiente de desenvolvimento integrado (IDE) que suporte o desenvolvimento para o Raspberry Pi Pico.

### 2. Comportamento Esperado

- Ao pressionar o botão de incremento, o número exibido na matriz de LEDs será incrementado.
- Ao pressionar o botão de decremento, o número exibido será decrementado.
- O LED indicador alternará seu estado periodicamente.


## Notas

- A implementação do debounce garante que os botões não registrem múltiplos cliques acidentais.
- A matriz de LEDs tem 25 pixels e é mapeada de forma a exibir os números de 0 a 9 corretamente.
  
## Vídeo da Execução
- https://youtu.be/ZMHjVfqoo1Y?feature=shared
