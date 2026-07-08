*This project has been created as part of the 42 curriculum by \<vebastos\>.*

Meta 2: O Arquiteto (Structs & Memória)Cria as tuas estruturas (t_coder, t_dongle, t_sim).Faz um malloc para criar arrays de coders e dongles dependendo do número de coders pedido.Inicializa todos os teus mutexes.Teste de sucesso: O programa arranca, aloca memória sem leaks (testa com Valgrind ou as flags de sanitize) e termina.

Meta 3: Hello World Multithread (Dar Vida aos Coders)Cria uma função simples (ex: coder_routine) que apenas faz um printf("Olá, sou o coder %d\n", id); e termina.No teu main, faz um loop com pthread_create para lançar todos os coders.Faz outro loop com pthread_join para esperar que todos acabem antes de fechar o programa.Teste de sucesso: Vais ver os "olás" a aparecerem no ecrã de forma desordenada (é normal, é a magia do paralelismo).

Meta 4: O Relógio e o Log (A Infraestrutura de Base)Cria uma função utilitária get_time_in_ms() que usa o gettimeofday.Cria uma função print_log() que tranca um mutex próprio de impressão, faz o printf com o timestamp correto, e destranca. Se não fizeres isto, os logs vão encavalar-se.  

Meta 5: O Caos Controlado (A Lógica Principal)Agora sim, escreves a verdadeira coder_routine (o loop infinito).Aplica a lógica de agarrar o dongle da esquerda e depois o da direita (cuidado com o deadlock: se todos agarrarem o da esquerda ao mesmo tempo, o programa bloqueia para sempre).Implementa o usleep para simular o tempo de cada estado (compilar, debug, refactor ).  

Meta 6: O Monitor (O Ceifeiro) e o SchedulerCria a thread do monitor que vai vigiar o relógio e matar a simulação se o tempo passar o time_to_burnout.  Implementa a heap para o teu scheduler lidar com filas de espera para os dongles.