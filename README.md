*This project has been created as part of the 42 curriculum by \<vebastos\>.*

1. A Inicialização Fina (Onde estamos agora): Preencher a memória que acabaste de alocar com os dados corretos. Atribuir IDs, inicializar os cadeados (mutexes) e ligar as mãos de cada programador aos adaptadores da esquerda e da direita.

2. O Big Bang (Criação de Threads): Construir o código que vai usar o pthread_create para transformar cada uma daquelas structs estáticas numa entidade "viva", a correr em paralelo dentro do sistema operativo.

3. A Rotina Principal (Core Loop): Escrever a função que todas as threads vão executar simultaneamente. É aqui que entra a lógica de tentar agarrar dongles, fazer um usleep para simular o tempo a compilar, imprimir no terminal com o timestamp correto, fazer debug e refatorizar.

4. O Vigilante (Monitor Thread): Criar uma thread isolada que funciona como a Dona Morte. Ela vai estar num loop infinito, a olhar para o relógio interno de cada programador, para ver se alguém excedeu o time_to_burnout. Se sim, ela bloqueia tudo e muda a flag is_running para 0.

5. O Encerramento (Cleanup): Quando o programa termina (seja por burnout ou sucesso), o teu main precisa de usar o pthread_join para recolher todas as threads, usar o pthread_mutex_destroy para destruir os cadeados, e dar free a toda a memória.





CLI : ./codexion 1 2 3 4 5 6 7 fifo