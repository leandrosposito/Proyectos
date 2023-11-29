#include <iostream>
#include <string.h>
#include <unordered_map>

typedef struct consumo{
	int anio;
	int mes;
	int dia;
	int hora;
	int minutos;
	int segundos;
	float consumo;
	char tipo[30];
	float temperatura;
	float potencia;
	float costo;
}consumo;

typedef struct Nodo{
    consumo data;
    Nodo* next;
}Nodo;

void lectura(FILE*,Nodo**,Nodo**,Nodo**,Nodo**);

void Pila(Nodo**,consumo);
void Lista(Nodo**,consumo);
void Cola (Nodo**, Nodo**, consumo);


//!LISTA ENLAZADA--------------------------------------
void mostrar(Nodo*);
float consumoTotal(Nodo*);
float consumomes(Nodo*,const int,const int);
float costomes(Nodo*,const int,const int);
std::string DispositivoIneficiente(Nodo*);
//!---------------------------------------------------


//! COLA----------------------------------------------
float promedio_consumo_diario(Nodo*,consumo,int,int,int);
void tendencia_consumo(Nodo*,consumo);
void consumo_tipo(Nodo*,consumo,int,int,int);
void identificarUmbral(Nodo*,const char*,const char*,float);
//!---------------------------------------------------

//! PILA------------------------------------------------
void consumo_acumulado(Nodo**);                
void fechayhora(Nodo**);						
void eficiencia(Nodo*);							
void costo_promedio(Nodo*);						
//!-----------------------------------------------------


int main(int argc,char*argv[]){

	Nodo* sp = NULL;
	Nodo* head = NULL;
	Nodo* front = NULL;
	Nodo* back = NULL;

	FILE* fp = NULL; 

	consumo c;

	int opc = 0,dia = 0,mes = 0,anio = 0;
	float umbral = 0.0;
	char dia1[20],mes1[20];
	
	
	lectura(fp,&sp,&front,&back,&head);
	

	do{
		printf("\n--- MENU DE OPCIONES---\n");
        printf("1. Mostrar Datos\n2. Lista Enlazada\n3. Colas\n4. Pilas\n5. Salir\nOPCION:");
        scanf("%d", &opc);

        if(opc!=5)system("cls");


		switch(opc){
			case 1: 
				mostrar(head); 
			break;
			case 2: 
				printf("\nIngrese el anio: ");
				scanf("%d",&anio);
				printf("Ingrese el mes para calcular el consumo: ");
				scanf("%d",&mes);

				system("cls");
				do {
					printf("\n--- LISTA ENLAZADA ---\n");
					printf("1. Consumo total acumulado\n2. Consumo de un mes\n3. Dispositivo mas ineficiente\n4. Costo total de un mes\n5. Salir\n");
					printf("---------------------------------------------\n");
					scanf("%d", &opc);

					switch (opc) {
						case 1:
							printf("El consumo total acumulado es de: %.2f\n", consumoTotal(head));
						break;
						case 2:			
							printf("Consumo del mes %d y anio %d: %.2f\n", mes, anio, consumomes(head, mes, anio));
							break;
						case 3:
							printf("Dispositivo ineficiente: %s\n", DispositivoIneficiente(head));
							break;
						case 4:

							printf("Costo total del mes: %.2f\n", costomes(head, mes, anio));
							break;
						default:
							printf("\nOpcion no definida ...");
							break;
					}
				} while (opc != 5);
			break;

			case 3:
				opc = 0;
				
				do{	
					printf("--- COLAS ---\n");
					printf("\n1. Consumo promedio de dia y mes en especifico.\n2. Calcular la tendencia de consumo.\n3. Mostrar Tendencia de consumo.\n4. Calcular el costo por tipo de dispositivo.\n5. Salir.\nOpcion:");
					scanf("%d", &opc);

					switch(opc){
						case 1:
							dia = 0,mes = 0,anio = 0;
							printf("\n Ingrese dia: ");
							scanf("%d",&dia);
							printf("Ingrese mes: ");
							scanf("%d", &mes);
							printf("Ingrese anio: ");
							scanf("%d", &anio);
							printf("El consumo promedio del dia seleccionado es: %.2f\n", promedio_consumo_diario(front,c,dia,mes,anio));
							system("pause()");
							system("cls");
							break;
						case 2:
							printf("Ingrese el dia: ");
							scanf("%d", &c.dia);
							printf("Ingrese el mes: ");
							scanf("%d", &c.mes);
							printf("Ingrese el anio: ");
							scanf("%d", &c.anio);
							tendencia_consumo(front, c);
							system("pause");
							system("cls");
							break;
						case 3:
							printf("Ingrese el dia para identificar dispositivos que superan el umbral de consumo: ");
							scanf("%s", dia1);
							
							printf("Ingrese el mes para identificar dispositivos que superan el umbral de consumo: ");
							scanf("%s", mes1);
							
							printf("Ingrese el umbral de consumo: ");
							scanf("%f", &umbral);
							
							identificarUmbral(front, dia1,mes1,umbral);
							break;
						case 4:
							printf("Ingrese anio: ");
							scanf("%d", &anio);
							printf("Ingrese mes: ");
							scanf("%d", &mes);
							printf("Ingrese dia: ");
							scanf("%d", &dia);

							consumo_tipo(front,c,dia,mes,anio );
							
							system("pause");
							system("cls");
							break;
						case 5:
							printf("Saliendo...\nGracias por usar nuestro programa\n");
							return 1;
							break;
						default:
							printf("Error en la seleccion , intente nuevamente");
							system("cls");
							break;
						}
				}while(opc!=5);
			break;

			case 4:
				opc = 0;
				do {
					printf("\n--- PILAS ---\n");
					printf("1. Consumo acumulado por dispositivo\n2. Identificar fecha y hora del maximo consumo de cada dispositivo\n3. Identificar el dispositivo con mayor eficiencia\n4. Costo promedio por tipo de dispositivo\n5. Salir\n");
					scanf("%d", &opc);

					if(opc!=5)system("cls");

					switch (opc){
						case 1: consumo_acumulado(&sp); break;
						case 2: fechayhora(&sp); break;
						case 3: eficiencia(sp); break;
						case 4: costo_promedio(sp); break;
						case 5: printf("\n\nSaliendo del programa...\n\n");break;
				
					}
				} while (opc != 5);
			break;
			case 5: 
				printf("Saliendo del programa....");
				exit(1);
			break;
			default: perror("OPCION INVALIDA..");break;
		}
	}while(opc!=5);

    return 0;
}

void lectura(FILE* fp, Nodo** sp,Nodo** front,Nodo** back,Nodo** head) {
    
	fp = fopen("dataset.txt","r");

	if (fp == NULL) {
		printf("No se pudo abrir el archivo\n");
		return ;
	}
	consumo c;
    while (fscanf(fp, "%d-%d-%d %d:%d:%d,%f,%[^,],%f,%f,%f\n",
               &c.anio, &c.mes, &c.dia, &c.hora, &c.minutos, &c.segundos,
               &c.consumo, c.tipo, &c.temperatura, &c.potencia, &c.costo)==11){
        Pila(sp,c);
		Cola(front,back,c);
		Lista(head,c);
    }
	fclose(fp);
	printf("Escaneo de archivo exitoso\n");
	system("pause");
	system("cls");
}
void Pila(Nodo** sp, consumo value){
	
	Nodo* new_node = (Nodo*)malloc(sizeof(Nodo)); 
	if (new_node == NULL) {
		printf("No hay memoria reservada");
		exit(0);
	}
	
	new_node->data = value;
	new_node->next = *sp;
	
	*sp = new_node;
}
void Lista(Nodo** head,consumo c){
    Nodo* newnodo = (Nodo*)malloc(sizeof(Nodo));

    if (newnodo == NULL) {
        printf("\nNo hay memoria disponible...");
        exit(1);
    }

    newnodo->data = c;
    newnodo->next = *head;

	*head = newnodo;

}
void Cola (Nodo** front, Nodo** back,consumo c){
	Nodo *temp = NULL;
		
	temp = (Nodo *) malloc(sizeof(Nodo));
		
	if(temp == NULL){
		printf("\nNo hay memoria disponible");
		exit(1);
	}
		
	temp -> data = c;
	temp -> next = NULL;
		
	if(*back == NULL){
		*back = temp;
		*front = *back;
	}else{
		(*back) -> next = temp;
		*back = temp;
	}
}
void mostrar(Nodo* head){

	Nodo* temp = head;

	while (temp != NULL) {
        printf("%d/%d/%d %d:%d:%d %.2f %s %.2f %.2f %.2f\n",
               temp->data.dia,temp->data.mes,temp->data.anio, temp->data.hora, temp->data.minutos,
               temp->data.segundos, temp->data.consumo, temp->data.tipo,
               temp->data.temperatura, temp->data.potencia, temp->data.costo);
        temp = temp->next;
    }
}
float consumoTotal(Nodo* head) {
    float suma = 0;
    Nodo* temp = head;

    while (temp != NULL) {
        suma += temp->data.consumo;
        temp = temp->next;
    }

    return suma;
}
// Leandro Sposito
float consumomes(Nodo* head, const int mes, const int anio) {
    float consumoMes = 0;
    Nodo* temp = head;

    while (temp != NULL) {
        if (temp->data.mes == mes && temp->data.anio == anio) {
            consumoMes += temp->data.consumo;
        }
        temp = temp->next;
    }

    return consumoMes;
}
float costomes(Nodo* head, const int mes, const int anio) {
    float costoMes = 0.0;
    Nodo* temp = head;

    while (temp != NULL) {
        if (temp->data.mes == mes && temp->data.anio == anio) {
            costoMes += temp->data.costo;
        }
        temp = temp->next;
    }

    return costoMes;
}

std::string DispositivoIneficiente(Nodo* head) {
   
    std::string ineficiencia;
    float maxConsumo = 0.0;
    Nodo* temp = head;

    while (temp != NULL) {
        if (temp->data.consumo > maxConsumo) {
            maxConsumo = temp->data.consumo;
            ineficiencia = temp->data.tipo;
        }
        temp = temp->next;
    }

    return ineficiencia;
}
float promedio_consumo_diario(Nodo* front, consumo c, int dia, int mes, int anio){
	
	Nodo *temp = NULL;
	int suma = 0, contador = 0;
	float prom = 0;
			
	temp = front;
			
	while( temp != NULL ){
		if(temp->data.dia == dia && temp->data.mes == mes && temp->data.anio == anio ){
			suma += temp->data.consumo;
			contador++;
		}
		temp = temp -> next;
	}
	if(contador == 0){
		printf("No hay datos de tal fecha\n");
	}
	prom = (float)suma/contador;
			
	return prom;
}

// Leandro Sposito
void tendencia_consumo(Nodo* front, consumo c){
	
	Nodo* temp = front;
	float consumo_anterior = 0;
	float consumo_actual = 0;
	char tendencia[] = "constante"; // Inicialmente, consideramos la tendencia como constante
				
	while (temp != NULL) {
		// Verificar si el nodo est? en el a?o, mes y d?a seleccionados
		if (temp->data.anio == c.anio && temp->data.mes == c.mes && temp->data.dia == c.dia) {
			consumo_actual = temp->data.consumo;
			// Comparar el consumo actual con el consumo anterior
			if (consumo_actual > consumo_anterior) {
				if (strcmp(tendencia, "descendente") == 0) {
				strcpy(tendencia, "constante"); // Si cambiamos de descendente a ascendente, la tendencia se vuelve constante
			} else {
					strcpy(tendencia, "ascendente"); // La tendencia es ascendente
				}
			} else if (consumo_actual < consumo_anterior) {
				if (strcmp(tendencia, "ascendente") == 0) {
					strcpy(tendencia, "constante"); // Si cambiamos de ascendente a descendente, la tendencia se vuelve constante
				} else {
					strcpy(tendencia, "descendente"); // La tendencia es descendente
				}
			}
		// Actualizar el consumo anterior para el pr?ximo nodo
			consumo_anterior = consumo_actual;
		}
		temp = temp->next;
	}
	printf("Tendencia: %s\n",tendencia);
}		
void consumo_tipo(Nodo* front,consumo c,int dia,int mes,int anio){
    Nodo* temp = front;
	float tipo1 = 0;
    float tipo2 = 0;
    float tipo3 = 0;
    float tipo4 = 0;
    while (temp != NULL) {
        if (temp->data.dia == dia && temp->data.mes == mes && temp->data.anio == anio) {
            if (strcmp(temp->data.tipo, "Aire Acondicionado") != 0) {
                tipo1 += temp->data.costo;
            } else if (strcmp(temp->data.tipo, "Iluminación") != 0) {
                tipo2 += temp->data.costo;
            } else if (strcmp(temp->data.tipo, "Calefacción") != 0) {
                tipo3 += temp->data.costo;
            } else if (strcmp(temp->data.tipo, "Electrodomésticos") != 0) {
                tipo4 += temp->data.costo;
            }
        }
        temp = temp->next;
    }
    printf("Costo por tipo:\n");
    printf("Aire acondicionada: %.2f\n", tipo1);
    printf("Iluminacion: %.2f\n", tipo2);
    printf("Calefaccion: %.2f\n", tipo3);
    printf("Electrodomesticos: %.2f\n", tipo4);
}
void identificarUmbral(Nodo* front, const char* dia, const char* mes, float umbral){
					
	printf("Dispositivos que superan el umbral de consumo en el día %s y el mes %s:\n", dia, mes);
	Nodo* temp = front;

    while (temp != NULL) {
        if (temp->data.dia == atoi(dia) && temp->data.mes == atoi(mes)) {
            if (temp->data.consumo > umbral) {
                printf("Dispositivo: %s, Consumo: %.2f\n", temp->data.tipo, temp->data.consumo);
            }
        }
        temp = temp->next;
    }
}
void consumo_acumulado(Nodo** sp){
   
    if (*sp == NULL) {
        printf("La pila está vacía.\n");
        return;
    }

    printf("Consumo acumulado por dispositivo: \n");

    Nodo* temp = *sp;

    float consu_acumulado = 0.0;
    std::string dispositivos_actual = "";

    while (temp != NULL) {
        consumo dato = temp->data;

        if (strcmp(dispositivos_actual.c_str(), dato.tipo) != 0) {
            if (!dispositivos_actual.empty()) {
                printf("Dispositivo: %s ,Consumo Acumulado: %.2f\n", dispositivos_actual.c_str(), consu_acumulado);
            }
            dispositivos_actual = dato.tipo;
            consu_acumulado = 0;
        }
        consu_acumulado += dato.consumo;
        temp = temp->next;
    }

    if (!dispositivos_actual.empty()) {
        printf("Dispositivo: %s ,Consumo Acumulado: %.2f\n", dispositivos_actual.c_str(), consu_acumulado);
    }
}

// Leandro Sposito
void fechayhora(Nodo** sp){ 

    if (*sp == NULL) {
        printf("La pila está vacía.\n");
        return;
    }

    printf("Fecha y hora del máximo consumo por dispositivo:\n");

    Nodo* temp = *sp;

    while (temp != NULL) {
        consumo dato = temp->data;
        float max_consumo = dato.consumo;
        std::string fecha_hora;

        while (temp != NULL && strcmp(temp->data.tipo, dato.tipo) == 0) {
            if (temp->data.consumo > max_consumo) {
                max_consumo = temp->data.consumo;
                fecha_hora = std::to_string(temp->data.anio) + "/" +
                              std::to_string(temp->data.mes) + "/" +
                              std::to_string(temp->data.dia) + " " +
                              std::to_string(temp->data.hora) + ":" +
                              std::to_string(temp->data.minutos) + ":" +
                              std::to_string(temp->data.segundos);
            }
            temp = temp->next;
        }
        printf("Dispositivo: %s, Fecha y hora del máximo consumo: %s\n", dato.tipo, fecha_hora.c_str());
    }
}
void eficiencia(Nodo* sp){
    
    if (sp == NULL) {
        printf("La pila esta vacia.\n");
        return;
    }

    float max_eficiencia = 0.0;
    char dispositivo_eficiente[30];

    Nodo* temp = sp;

    while (temp != NULL) {
        consumo dato = temp->data;
        float eficiencia = dato.consumo / dato.potencia;

        if (eficiencia > max_eficiencia) {
            max_eficiencia = eficiencia;
            strcpy(dispositivo_eficiente, dato.tipo);
        }

        temp = temp->next;
    }

    printf("El dispositivo mas eficiente es: %s con una eficiencia de: %.2f\n", dispositivo_eficiente, max_eficiencia);
}
void costo_promedio(Nodo* sp) {
    if (sp == NULL) {
        printf("La pila está vacía.\n");
        return;
    }
    std::unordered_map<std::string, float> costo_total;
    std::unordered_map<std::string, int> contador;
    Nodo* temp = sp;
    while (temp != NULL) {
    
        std::string tipo = temp->data.tipo;
        costo_total[tipo] += temp->data.costo;
        contador[tipo]++;
        temp = temp->next;
    
    }
    printf("Costo promedio por tipo:\n");
    for (const auto& entry : costo_total){
        const std::string& tipo = entry.first;
        float costo = entry.second;
        int cantidad = contador[tipo];
        if (cantidad > 0) {
            printf("%s: %.2f\n", tipo.c_str(), costo / cantidad);
        } else {
            printf("%s: No hay datos disponibles\n", tipo.c_str());
        }
    }
}