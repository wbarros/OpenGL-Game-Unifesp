# OpenGL-Game-Unifesp
Jogo/Animação em OpenGL com linguagem C, projeto da matéria de processamento de imagens 

O jogo ....
O objetivo como uma função é simples colher todas as frutas clicadas com o botão do
mouse, e retornar a um ponto específico com o balde de frutas em mãos. O personagem não é
controlável, ou seja, suas tarefas apos um clique é automática e ele persegue o clique do
mouse ao aparecer uma fruta na árvore, enquanto o humanoide esta buscando uma fruta
podese
clicar em outras arvores para aparecerem mais frutas essas frutas são adicionadas em
um vetor de filas onde a busca será feita na ordem de FIFO. Após colher todas frutas, se e
somente se, todas frutas estiverem colhidas e ainda pelo menos uma fruta tem que ser colhida
para poder finalizar a tarefa, assim então no menu de opção terá a opção de finalizar tarefa.

Como rodar o trabalho ?
O projeto foi criado na plataforma Windows, logo o caminho das texturas estão
conforme o windows, ao criar o projeto terá que importar no mesmo personagem.cpp e os
cabeçalhos personagem.h e mapa.h (por causa das texturas no mapa) deixei as funções deles
na main.cpp. Depois que construido o projeto clique em qualquer árvore irá aparecer uma
ruta e o personagem ira colher esta fruta depois que repetir isso quantas vezes quiser abra o
menu com o botão direito e clique em finalizar tarefa.

Opções do teclado
● Braço Esquerdo
○ Tecla ‘Q’ ou ‘q’, rotaciona braço inteiro em X.
○ Tecla ‘A’ ou ‘a’, rotaciona braço inteiro em Z.
○ Tecla ‘W’ ou ‘w’, rotaciona antebraço em X.
○ Tecla ‘S’ ou ‘s’, rotaciona pulso em X.
○ Tecla ‘E’ ou ‘e’, rotaciona pulso em Y.
○ Tecla ‘D’ ou ‘d’, rotaciona pulso em Z.
● Braço Direito
○ Tecla ‘R’ ou ‘r’, rotaciona braço inteiro em X.
○ Tecla ‘F’ ou ‘f’, rotaciona braço inteiro em Z.
○ Tecla ‘T’ ou ‘t’, rotaciona antebraço em X.
○ Tecla ‘G’ ou ‘g’, rotaciona pulso em X.
○ Tecla ‘H’ ou ‘h’, rotaciona pulso em Y.
○ Tecla ‘U’ ou ‘u’, rotaciona pulso em Z.
● Perna Esquerda
○ Tecla ‘I’ ou ‘i’, rotaciona perna inteira em X.
○ Tecla ‘J’ ou ‘j’, rotaciona perna inteira em Z.
○ Tecla ‘O’ ou ‘o’, rotaciona canela em X.
○ Tecla ‘K’ ou ‘k’, rotaciona pé em X.
○ Tecla ‘p’ ou ‘p’, rotaciona pé em Y.
● Perna Direita
○ Tecla ‘L’ ou ‘l’, rotaciona perna inteira em X.
○ Tecla ‘M’ ou ‘m’, rotaciona perna inteira em Z.
○ Tecla ‘N’ ou ‘n’, rotaciona canela em X.
○ Tecla ‘B’ ou ‘b’, rotaciona pé em X.
○ Tecla ‘V’ ou ‘v’, rotaciona pé em Y.
● ZOOM
○ Tecla ‘+’, ZOOMIN.
○ Tecla ‘’,
ZOOMOUT.
● Rotação da câmera
○ Tecla ‘X’ ou ‘x’, rotaciona câmera em X.
○ Tecla ‘Y’ ou ‘y’, rotaciona câmera em Y.
○ Tecla ‘Z’ ou ‘z’, rotaciona câmera em Z.
3.2 Opções do mouse
● Clique esquerdo
○ Se for um clique em uma árvore e aparecer uma fruta o personagem irá
buscar a fruta.
● Clique direito
○ Abre o menu de opções.
● Menu
○ 1 → finaliza a tarefa
○ 2 → sai do programa
○ 3 → a partir desse ponto os comandos serão apenas feito por
teclado. (opções do mouse)
