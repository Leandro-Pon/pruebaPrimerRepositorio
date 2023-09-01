/*
Bas�ndose en su c�digo fuente de su ejercicio 4 del TP4 de archivos, va a trabajar con
listas enlazadas para una base de datos de im�genes.
Puede tener pre-cargada algunos nodos a su lista. La lista debe ser simplemente
enlazada.
Debe crear funciones que permitan al usuario:
? a�adir un nodo a la lista,
? eliminarlo de la lista,
? guardar la lista completa en un archivo ( modo append y binario),
? recuperar/leer esa lista del archivo,
? realizar b�squedas: por cualquiera de los miembros de la estructura imagen (tipo
archivo, nombre, etc). En el caso del tama�o del archivo, especificar si se busca
mayor a X tama�o (ingresado por teclado) o menor a X o un valor exacto de
tama�o.
? Mostrar la lista para visualizar todos sus elementos.
? Mostrar la lista ordenada alfab�ticamente seg�n el nombre del archivo.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct Stock{	
	int cod; 			 // c�digo de inventario
	char nom_arch[25];   // nombre de archivo
	char ext[10]; 		 // extenci�n del archivo
	int tam_byt;  	  	 // tama�o en bytes del archivo
	float precio;  		 // precio de la imagen
	struct Stock *next;
};
struct Stock *lista = NULL;

void NuevoNodo();
void ElimNodo();
void MostrarLista(struct Stock *lista);
void GuardarLista();
void ListaArch();
void BusCod();
void BusNom();
void BusExt();
void BusTam();
void BusPre();
void MostListAlfa();

int main() {
	
	int n;
	printf("	Bienvenido! - Seleccione una opci�n.\n");
	
	do{
	printf("\n1 - Agregar una imagen\n");
	printf("2 - Eliminar una imagen\n");
	printf("3 - Guardar la lista en un archivo\n");
	printf("4 - Leer la lista desde un archivo\n");
	printf("5 - Buscar por c�digo\n");
	printf("6 - Buscar por nombre de archivo\n");
	printf("7 - Buscar por extenci�n\n");
	printf("8 - Buscar por tama�o en bytes\n");
	printf("9 - Buscar por precio\n");
	printf("10 - Mostrar la lista\n");
	printf("11 - Ordenar la lista alfalfab�ticamente\n");
	printf("12 - Salir.\n\n Selecci�n: ");
	scanf("%d", &n);
	
	switch (n){
		case 1:
			NuevoNodo(lista);
		break;
		
		case 2:
			ElimNodo(lista);
		break;
		
		case 3:
			GuardarLista(lista);
		break;
		
		case 4:
			ListaArch();
		break;
		
		case 5:
			BusCod();
		break;
		
		case 6:
			BusNom();
		break;
		
		case 7:
			BusExt();
		break;
		
		case 8:
			BusTam();
		break;
		
		case 9:
			BusPre();
		break;
		
		case 10:
			if(lista==NULL){
				printf("\nNo se ingres� ning�n elemento.\n");
			}
			else{
				MostrarLista(lista);
			}
		break;	
		
		case 11:	
			MostListAlfa();
		break;
	}
	}while((n<12)&&(n>0));
	return 0;
}
void NuevoNodo(){
		
	struct Stock *nuevo = (struct Stock*)malloc(sizeof(struct Stock));

		printf("\n Ingrese el c�digo de inventario: ");
		scanf("%d", &nuevo->cod);
		fflush(stdin);
	
		printf("\n Ingrese el nombre del archivo: ");
		fgets(nuevo->nom_arch, 25, stdin);
	
		printf("\n Ingrese la extenci�n del archivo o tipo de imagen: ");
		fgets(nuevo->ext, 10, stdin);
	
		printf("\n Ingrese el tama�o en bytes del archivo: ");
		scanf("%d", &nuevo->tam_byt);
		fflush(stdin);

		printf("\n Ingrese el precio de la imagen: ");
		scanf("%f", &nuevo->precio);
		fflush(stdin);
	
		if(lista==NULL){
			nuevo->next=NULL;
			lista=nuevo;
		}else{
		nuevo->next=lista;
		lista=nuevo;
		}
		
}
void ElimNodo(){
	int codElim; //variable que indica el c�digo de la imagen que desea eliminar
	if (lista != NULL)
	{
		printf("\n Ingrese el c�digo de inventario de la imagen que desea eliminar: ");
		scanf("%d", &codElim);
		struct Stock *aux; 
		struct Stock *anterior;  
		anterior=NULL;
		aux=lista;
		
		while((aux != NULL) && (aux->cod != codElim))
		{
			anterior = aux;
			aux = aux->next;
		}
		if(aux == NULL)	//No existe ese elemento
		{
			printf("\n No hay imagen alguna con ese c�digo de inventario");
		}
		else if(anterior == NULL)	//se elimina el primer elemento
		{
			lista = lista->next;
			free(aux);
			printf("\n Se elimin� la imagen de c�digo: %d con �xito.\n",  codElim);
		}
		else	//se elimina un elemento que no es el primero
		{
			anterior->next = aux->next;
			free(aux);
			printf("\n Se elimin� la imagen de c�digo: %d con �xito.\n",  codElim);
		}
	}
	else
	{
		printf("\n La lista est� vac�a\n");
	}
	
}
	
void GuardarLista(){
	if(lista==NULL){
		printf("\nERROR, no ingres� ninguna imagen.");
	}else
	{
		FILE *archivo;
		struct Stock *aux; 
		aux=lista;

		archivo = fopen("Lista.bin", "ab+");
		if (archivo != NULL){
			do{
			fwrite(aux,sizeof(struct Stock), 1, archivo);
			aux=aux->next;
			}while(aux!=NULL);
			fclose(archivo);
			printf("\nSe cre� el archivo con �xito\n.");
		}else {printf("\nERROR al abrir el archivo.\n");}
	}
}
void ListaArch(){
	FILE *archivo;
	struct Stock *listArc;	//es el puntero al primer elemento
	listArc=NULL;
	struct Stock imagen;
	
	archivo = fopen("Lista.bin", "rb");
	if (archivo != NULL){
		while(!feof(archivo)){
			struct Stock *nuevo = (struct Stock*)malloc(sizeof(struct Stock));
			fread(&imagen,sizeof(struct Stock), 1, archivo);
			*nuevo=imagen;
			nuevo->next=listArc;
			listArc=nuevo;
		}
		fclose(archivo);
		MostrarLista(listArc);
	}else {printf("\nERROR al abrir el archivo.\n");}
}
	
void BusCod(){
	if (lista != NULL)
	{	
		int codBus;
		struct Stock *aux;
		aux=lista;
		
		printf("\n Ingrese el c�digo de inventario de la imagen que desea buscar: ");
		scanf("%d", &codBus);
		if(aux->cod==codBus){
			printf("\n	----	----");
			printf("\n C�digo de inventario: %d", aux->cod);
			printf("\n Nombre del archivo: %s", aux->nom_arch);
			printf(" Extenci�n del archivo o tipo de imagen: %s", aux->ext);
			printf(" Tama�o en bytes del archivo: %d", aux->tam_byt);
			printf("\n Precio de la imagen: %.2f", aux->precio);
			printf("\n	----	----");
		}else{printf("\n No hay una imagen con ese c�digo en la lista\n");}
	}else {printf("\n No se creo ninguna lista\n");}
	}
void BusNom(){
	if (lista != NULL)
	{	
		char nom[20];
		struct Stock *aux;
		aux=lista;
			
		printf("\n Ingrese el nombre de la imagen que desea buscar: ");
		fflush(stdin);
		fgets(nom, 25, stdin);
		if(strcmp(aux->nom_arch,nom)==0){
			printf("\n	----	----");
			printf("\n C�digo de inventario: %d", aux->cod);
			printf("\n Nombre del archivo: %s", aux->nom_arch);
			printf(" Extenci�n del archivo o tipo de imagen: %s", aux->ext);
			printf(" Tama�o en bytes del archivo: %d", aux->tam_byt);
			printf("\n Precio de la imagen: %.2f", aux->precio);
			printf("\n	----	----");
		}else{printf("\n No hay una imagen con ese nombre en la lista\n");}
	}else {printf("\n No se creo ninguna lista\n");}
	}
void BusExt(){
	if (lista != NULL)
	{	
		char ext[20];
		struct Stock *aux;
		aux=lista;
		
		printf("\n Ingrese la extenci�n de la imagen que desea buscar: ");
		fflush(stdin);
		fgets(ext, 25, stdin);
		if(strcmp(aux->ext,ext)==0){
			printf("\n	----	----");
			printf("\n C�digo de inventario: %d", aux->cod);
			printf("\n Nombre del archivo: %s", aux->nom_arch);
			printf(" Extenci�n del archivo o tipo de imagen: %s", aux->ext);
			printf(" Tama�o en bytes del archivo: %d", aux->tam_byt);
			printf("\n Precio de la imagen: %.2f", aux->precio);
			printf("\n	----	----");
		}else{printf("\n No hay una imagen con esa extenci�n en la lista\n");}
	}else {printf("\n No se creo ninguna lista\n");}
}
	
void BusTam(){
	if (lista != NULL)
	{	
		int tamBus;
		struct Stock *aux;
		aux=lista;
		
		printf("\n Ingrese el tama�o de la imagen que desea buscar: ");
		scanf("%d", &tamBus);
		if(aux->tam_byt==tamBus){
			printf("\n	----	----");
			printf("\n C�digo de inventario: %d", aux->cod);
			printf("\n Nombre del archivo: %s", aux->nom_arch);
			printf(" Extenci�n del archivo o tipo de imagen: %s", aux->ext);
			printf(" Tama�o en bytes del archivo: %d", aux->tam_byt);
			printf("\n Precio de la imagen: %.2f", aux->precio);
			printf("\n	----	----");
		}else{printf("\n No hay una imagen con ese tama�o en la lista\n");}
	}else {printf("\n No se creo ninguna lista\n");}
}

void BusPre(){
	if (lista != NULL)
	{	
		int preBus;
		struct Stock *aux;
		aux=lista;
		
		printf("\n Ingrese el precio de la imagen que desea buscar: ");
		scanf("%d", &preBus);
		if(aux->precio==preBus){
			printf("\n	----	----");
			printf("\n C�digo de inventario: %d", aux->cod);
			printf("\n Nombre del archivo: %s", aux->nom_arch);
			printf(" Extenci�n del archivo o tipo de imagen: %s", aux->ext);
			printf(" Tama�o en bytes del archivo: %d", aux->tam_byt);
			printf("\n Precio de la imagen: %.2f", aux->precio);
			printf("\n	----	----");
		}else{printf("\n No hay una imagen con ese precio en la lista\n");}
	}else {printf("\n No se creo ninguna lista\n");}
}
	
void MostrarLista(struct Stock *lis){
	struct Stock *aux; //variable auxiliar para mostrar los elementos de la lista
	aux=lis;
	do{
	printf("\n	----	----");
	printf("\n C�digo de inventario: %d", aux->cod);
	printf("\n Nombre del archivo: %s", aux->nom_arch);
	printf(" Extenci�n del archivo o tipo de imagen: %s", aux->ext);
	printf(" Tama�o en bytes del archivo: %d", aux->tam_byt);
	printf("\n Precio de la imagen: %.2f", aux->precio);
	printf("\n	----	----");
	aux=aux->next;
	}while(aux!=NULL);
}
void MostListAlfa(){	
	struct Stock *i;
	struct Stock *j;
	
	if(lista==NULL){
		printf("\nNo se ingres� ninguna lista.\n");
	}else{
		i=lista;
		//se usa el m�todo de la burbuja para ordenar la lista
	while(i!=NULL){
		j=i->next;
		while(j!=NULL){
			if(strcmp(i->nom_arch,j->nom_arch)>0){
				struct Stock *aux=(struct Stock*)malloc(sizeof(struct Stock));
				//aux=i;
				aux->cod=i->cod;
				strcpy(aux->nom_arch,i->nom_arch);
				strcpy(aux->ext,i->ext);
				aux->tam_byt=i->tam_byt;
				aux->precio=i->precio;
				
				//i=j;
				i->cod=j->cod;
				strcpy(i->nom_arch,j->nom_arch);
				strcpy(i->ext,j->ext);
				i->tam_byt=j->tam_byt;
				i->precio=j->precio;
				
				//j=aux;
				j->cod=aux->cod;
				strcpy(j->nom_arch,aux->nom_arch);
				strcpy(j->ext,aux->ext);
				j->tam_byt=aux->tam_byt;
				j->precio=aux->precio;
			}
		j=j->next;
		}
	i=i->next;
	}
	MostrarLista(lista);
	}
}
