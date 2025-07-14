            #include <iostream>
            #include <vector>
            #include <memory>
            #include <thread>
            #include <chrono>
            #include "Tablero.h"
            #include "Avatar.h"
            #include "AvatarCPU.h"
            #include "AvatarInnovador.h"
            #include "Juego.h"
            #include "LogicaDeMovimiento.h"
            #include "VistaConsola.h"

            int main() {
                std::cout << "=== BIENVENIDO AL JUEGO AVATAR CON POLIMORFISMO ===\n\n";

                // Crear tablero automáticamente
                Tablero tablero;
                std::cout << "Generando tablero automáticamente...\n";

                // Crear jugadores usando polimorfismo
                std::vector<IPersonaje*> jugadores;

                // Crear Avatar humano
                Avatar* avatarHumano = new Avatar();
                avatarHumano->setPosicionFila(1);
                avatarHumano->setPosicionColumna(1);
                jugadores.push_back(avatarHumano);

                // Crear AvatarCPU
                AvatarCPU* avatarCPU = new AvatarCPU();
                avatarCPU->setPosicionFila(1);
                avatarCPU->setPosicionColumna(2);
                avatarCPU->setTablero(&tablero);
                jugadores.push_back(avatarCPU);

                // Crear AvatarInnovador
                AvatarInnovador* avatarInnovador = new AvatarInnovador();
                avatarInnovador->setPosicionFila(2);
                avatarInnovador->setPosicionColumna(1);
                avatarInnovador->setTablero(&tablero);
                jugadores.push_back(avatarInnovador);

                // Crear lógica de movimiento
                LogicaDeMovimiento logicaMovimiento;

                // Crear juego
                Juego juego(&tablero, jugadores, &logicaMovimiento);

                // Crear vista
                VistaConsola vista(&tablero, jugadores);

                std::cout << "\n=== CONTROLES ===\n";
                std::cout << "W/w = Arriba\n";
                std::cout << "S/s = Abajo\n";
                std::cout << "A/a = Izquierda\n";
                std::cout << "D/d = Derecha\n";
                std::cout << "Q/q = Salir\n";
                std::cout << "\nObjetivo: Llegar a la salida (X)\n";
                std::cout << "Nota: Solo el Avatar humano puede terminar el juego cayendo en un abismo.\n";
                std::cout << "      Los otros avatares simplemente desaparecen si caen.\n";
                std::cout << "Presione Enter para comenzar...";
                std::cin.ignore();
                std::cin.get();

                // Bucle principal del juego
                while (juego.getEstado()) {
                    // Mostrar el estado actual del juego
                    vista.mostrarJuego();

                    // Verificar condición de victoria
                    juego.mover();
                    if (!juego.getEstado()) {
                        break;
                    }

                    // Obtener entrada del usuario para el Avatar humano
                    vista.mostrarMensaje("Ingrese movimiento para Avatar (W/A/S/D) o Q para salir:");
                    char entrada = vista.getEntradaConsola();

                    // Verificar si el usuario quiere salir
                    if (entrada == 'q' || entrada == 'Q') {
                        juego.terminar();
                        break;
                    }

                    // Mover Avatar humano
                    std::vector<IPersonaje*> soloAvatarHumano = {avatarHumano};
                    logicaMovimiento.mover(soloAvatarHumano, entrada);

                    // Verificar si el Avatar humano ganó o perdió
                    juego.mover();
                    if (!juego.getEstado()) {
                        break;
                    }

                    // Mover AvatarCPU automáticamente (solo si está activo)
                    if (avatarCPU->estaActivo()) {
                        std::vector<IPersonaje*> soloAvatarCPU = {avatarCPU};
                        logicaMovimiento.mover(soloAvatarCPU, '\0'); // Pasar '\0' para que AvatarCPU decida su movimiento
                    }

                    // Verificar estado del juego después del movimiento del AvatarCPU
                    juego.mover();
                    if (!juego.getEstado()) {
                        break;
                    }

                    // Mover AvatarInnovador automáticamente (solo si está activo)
                    if (avatarInnovador->estaActivo()) {
                        std::vector<IPersonaje*> soloAvatarInnovador = {avatarInnovador};
                        logicaMovimiento.mover(soloAvatarInnovador, '\0'); // Pasar '\0' para que AvatarInnovador decida su movimiento
                    }

                    // Verificar estado del juego después del movimiento del AvatarInnovador
                    juego.mover();
                    if (!juego.getEstado()) {
                        break;
                    }

                    // Pequeña pausa para hacer el juego más jugable
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                }

                // Mostrar estado final del juego
                vista.mostrarJuego();
                std::cout << "\n¡Gracias por jugar!\n";

                // Liberar memoria
                delete avatarHumano;
                delete avatarCPU;
                delete avatarInnovador;

                return 0;
            }