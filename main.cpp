#include <iostream>
#include <string>
#include <windows.h>
#include "pasajero.h"
#include "design.h"
#define ARRIBA 72
#define ABAJO 80
#define ENTER 13
#define SALIR 27

using namespace std;

design d;
string usuarios[1000][3];
string buses[6][2];
string horarios[3];
string disponibles[]{"01","02","03","04","05","06","07","08","09","10","11","12","13","14","15","16","17","18","19","20"};
string pasajeros[1000][6];
string nombre, ncuenta, contrasena;
int fila=0, pos=0, np = 1, lleno=0;

class menus{
	public:
		int gotoxy(USHORT x,USHORT y);
		void menu_principal();
		void menu_pasajero();
		int menu(const char titulo[], const char *opciones[], int n);		
	protected:
};

menus m;

void reservar(){

int dispo = 0;
int n, h, a;
string ruta, hr, bus;

	d.gotoxy(40,2);cout<<"Reservando asiento - "<<usuarios[pos][0];
	d.gotoxy(5,5);printf("Destinos disponibles: ");
for(int i = 0; i < 6; i++){d.gotoxy(8,6+i);cout<<i+1<<") "<<buses[i][1];}
	d.cursor(true);
	d.gotoxy(5,11);printf("Escriba el numero de la ruta en la cual desea viajar: ");
	d.gotoxy(59,11);cin>>n;
	
 if(n < 1 || n > 5){ 	
 	d.gotoxy(5,13);printf("No existe la ruta seleccionada. Por favor vuelva a intentarlo.");
	Sleep(1500);
	m.menu_pasajero();
	system("cls");
 }else{
 	n--;
		 		bus  = buses[n][0];
				ruta = buses[n][1];
			 	system("cls");
			 	d.gotoxy(40,2);cout<<"Reservando asiento - "<<usuarios[pos][0];
			 	d.gotoxy(5,4);cout<<"Ha seleccionado viajar hacia "<<ruta<<" el bus diponible es "<<bus;
			 	d.gotoxy(5,4);cout<<"Asientos disponibles: "<<bus;
			 	d.gotoxy(5,6);printf("Seleccione el horario: \n 	1) 06:00 AM \n 	2) 12:00 PM \n 	3) 03:00 PM");
			 	d.gotoxy(5,11);printf("Escriba el numero de horario: ");
			 	d.gotoxy(35,11);cin>>h;
		 	if(h <1 || h > 3){
		 		d.gotoxy(5,13);printf("No existe el horario seleccionado. Por favor vuelva a intentarlo.");
				Sleep(1500);
				m.menu_pasajero();
				system("cls");
			 }else{
			 	hr = horarios[h-1];
				system("cls");	
				d.gotoxy(40,2);cout<<"Reservando asiento - "<<usuarios[pos][0];
				d.gotoxy(5,4);cout<<"Ha seleccionado viajar hacia "<<ruta<<" el bus diponible es "<<bus<<" en horario "<<horarios[h-1]<<endl;
			  /*pasajeros[0][0]="admin";
				pasajeros[0][1]="Bus No. 0001";
				pasajeros[0][2]="Villanueva";
				pasajeros[0][3]="06:00 AM";
				pasajeros[0][4]="0";
				pasajeros[0][5]="Confirmado";*/
					  for(int i = 0; i < np;i++){
						if(pasajeros[i][5]!="Cancelado"){
							lleno++;	
							const char* as = pasajeros[i][4].data();
							int n = atoi(as);
							if((pasajeros[i][1]==bus) && (pasajeros[i][2]==ruta) && (pasajeros[i][3]==hr)){
							disponibles[n]= "--";				
							}	
						}	
					}
							dispo = 20 - lleno;
						if(dispo==0){
							d.gotoxy(5,13);printf("No hay asientos disponibles en este horario.");	
							Sleep(1500);
							m.menu_pasajero();
							system("cls");		
						}else{
							d.gotoxy(5,6);"Asientos disponibles: ";
							d.gotoxy(5,7);
							for(int i = 0; i < 10;i++){cout<<disponibles[i]<<" | ";} 
							d.gotoxy(5,8);
							for(int i = 10; i < 20;i++){cout<<disponibles[i]<<" | ";} 
							cout<<endl;
							system("pause");
					 		}	
						}
						//Revisando si el usuario esta dentro de la matriz asientos.
						
 					}
 				}
void password(string &value){
	char key;
	value.empty();
	do
		{
		key = getch();
		 switch (key)
		 {
			case '\b':
			if(value.length() > 0)
			{
				value.erase(value.length() - 1, 1);
				std::cout << '\b' << " " << '\b';
			}
				break;
				default:
					if(key > 31 && key < 127)   //Only no control characters are valid
					 {
						value.push_back(key);
						std::cout << "*";
					  }
		  }
	} while(key != '\r'); //Quit if Enter is Pressed
}
void login_user(){
	inicio:
	contrasena = "";
	pos = 0;
	bool login;	
	d.cursor(true);
	system("cls");
	d.menu();
	d.gotoxy(5,5);
	d.SetColor( 15 );
	printf("No. cuenta: ");
	d.gotoxy(5,7);
		printf("Contraseña: ");
		d.SetColor( 13 );
		d.gotoxy(17,5);cin>>ncuenta;
		d.gotoxy(17,7);password(contrasena);
		for(int i=0; i <= fila; i++){
					if(ncuenta==usuarios[i][1]) pos = i;			
				}
   				if((ncuenta==usuarios[pos][1]) && (contrasena==usuarios[pos][2])){
					d.cargando();
					m.menu_pasajero();
				   }else{
					   	d.SetColor(12);
					   	d.gotoxy(5,9);
					   	printf("El usuario o contraseña son incorrectos. Por favor Intente de nuevo.");
					   	d.SetColor(15);
						Sleep(1000);
				   }
			}
void registrar(){
	inicio:
	string cuenta, pass, nom;	
	int validar=0;
	d.registro();
	d.cursor(true);
	d.SetColor( 15 );
	d.gotoxy(5,5);
	printf("Nombre: ");
	d.gotoxy(5,6);
	printf("No. Cuenta: ");
	d.gotoxy(5,7);
		printf("Contraseña: ");
		d.SetColor( 6 );
		d.gotoxy(13,5);std::getline(std::cin, nom);
		d.gotoxy(17,6);cin>>cuenta;
		d.gotoxy(17,7);password(pass);
			fila+=1;	
			if(cuenta.length()>1 && pass.length()>1){
				for(int i=0; i <= fila; i++){if(!cuenta.compare(usuarios[i][1])) validar+=1;}
			if(validar == 0 ){
				usuarios[fila][0]=nom;
				usuarios[fila][1]=cuenta;
				usuarios[fila][2]=pass;
				d.cursor(false);
				d.gotoxy(5,9);printf("El usuario ha sido ingresado exitosamente!");
				Sleep(1500);
			}else{
				fila-=1;
				d.cursor(false);
				d.gotoxy(5,9);printf("El usuario ya existe!");
				Sleep(1000);
				system("cls");
			}
			}else{
				fila-=1;
				d.cursor(false);
				d.gotoxy(5,9);printf("Los datos ingresados no son validos! Presione ENTER, para continuar.");
				Sleep(1000);
				system("cls");
			}
		}
 	int menus::gotoxy(USHORT x,USHORT y) {
   		COORD cp = {x,y};
   		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cp);
	}
		int menus::menu(const char titulo[], const char *opciones[], int n){
		   int seleccion = 1;
		   int tecla;
		   bool repite = true; 
		   	do {
		    		system("cls");
		      	// Imprime el título del menú
		      		d.SetColor(15);
				  	gotoxy(15, 2); cout << titulo;
		      	// Imprime las opciones del menú
		      		d.SetColor(12);
		      		gotoxy(7, 3 + seleccion); cout << ">>" << endl;
		      		
			for (int i = 0; i < n; ++i) {
				if(seleccion==i+1){
			      		d.SetColor(12);
			      		gotoxy(10, 4 + i); cout << i + 1 << ") " << opciones[i];
					  }	else {
					  	d.SetColor(15);
					  	gotoxy(10, 4 + i); cout << i + 1 << ") " << opciones[i];
					  }
			      	}
		      		// Solo permite que se ingrese ARRIBA, ABAJO o ENTER
		      		d.SetColor(15);
			do {
		    	tecla = getch();
		         //gotoxy(15, 15); cout << "tecla presionada: " << (char)tecla << " = " << tecla;
		      	}while(tecla != ARRIBA && tecla != ABAJO && tecla != ENTER);
		      		switch (tecla) {
		         	case ARRIBA:   // En caso que se presione ARRIBA
		            	seleccion--;
		            	if (seleccion < 1) {
		               	seleccion = n;
		            	}
		            	break;
		         	case ABAJO:
		            	seleccion++;
		            	if (seleccion > n) {
		               	seleccion = 1;
		            	}
		            	break;
		         	case ENTER:
		            	repite = false;
		            	break;
		      					}
		   					}while (repite);
		   					return seleccion;
									}	
	void menus::menu_principal(){
		   d.cursor(false);

		   bool repite = true;
		   int opcion;   
		   const char *titulo = "SISTEMA CONTROL DE BUSES - MENU DE OPCIONES";
		   const char *opciones[] = {"INICIAR SESION", "REGISTRAR USUARIO", "SALIR"};
		   int n = 3; 
		   do {
		      opcion = menu(titulo, opciones, n);
		      switch (opcion) {
		         case 1:
		         	system("cls");
		           	login_user();
		           	cin.ignore();
		            break;
		         case 2:
		         	system("cls");
		         	registrar();
		         	cin.ignore();
		            break;
		         case 3:
		            cout << "\nEl programa se cerrara!! Hasta pronto." << endl;
		            repite = false;
		            break;
		      }
		      
		   } while(repite);
		}
		void menus::menu_pasajero(){
			 d.cursor(false);
		   	bool repite = true;
		   	int opcion;   
		   	string tl = "Bienvenido al Sistema - "+ usuarios[pos][0];
	
			const char *titulo = tl.data();
		   
		   const char *opciones[] = {"RESERVAR", "CONFIRMAR RESERVA", "CANCELAR RESERVA", "IMPRIMIR TICKET","SALIR"};
		   int n = 5; 
		   do {
		      opcion = menu(titulo, opciones, n);
		      switch (opcion) {
		         case 1:
		         	system("cls");
		         	reservar();
		            break;
		         case 2:
		         	
		         	system("cls");
		            break;
		         case 3:
		         	
		         	system("cls");
		            break;
				 case 4:
		         	
		         	system("cls");
		            break;	   
		         case 5:
		            cout << "\nVolviendo al menu principal. Muchas gracias!" << endl;
		            repite = false;
		            d.cursor(false);
		            m.menu_principal();
		            Sleep(2000);
		            break;
		      }
		   } while(repite);
		}
int main(int argc, char** argv) {
	
		pasajeros[0][0]="admin";
		pasajeros[0][1]="Bus No. 0001";
		pasajeros[0][2]="Villanueva";
		pasajeros[0][3]="06:00 AM";
		pasajeros[0][4]="7";	
		pasajeros[0][5]="Confirmado";	
		
		
		usuarios[fila][0]="Admininistrador";
		usuarios[fila][1]="admin";
		usuarios[fila][2]="admin";
				
		buses[0][0]="Bus No. 0001";
		buses[0][1]="Villanueva";
		
		buses[1][0]="Bus No. 0002";
		buses[1][1]="Cortes";
		
		buses[2][0]="Bus No. 0003";
		buses[2][1]="Progreso";
		
		buses[3][0]="Bus No. 0004";
		buses[3][1]="Centro";
		
		buses[4][0]="Bus No. 0005";
		buses[4][1]="Barbara";
		
		buses[5][0]="Bus No. 0006";
		buses[5][1]="Sede Norte";
		
		horarios[0]="06:00 AM";
		horarios[1]="12:00 PM";
		horarios[2]="03:00 PM";
				
		m.menu_principal();
		
		return 0;
	}	


		

								
	
