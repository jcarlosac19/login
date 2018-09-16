//Control de rutas de buses y pasajeros, Cesar y Juan
#include <iostream>
#include <string>
#include <windows.h>
#include <limits>
#include <stdexcept>
#include <sstream>
#include <conio.h>
#define ARRIBA 72
#define ABAJO 80
#define ENTER 13
#define SALIR 27

using namespace std;

string usuarios[1000][3];
string buses[7][2];
string horarios[4];
int asientos[21];
string pasajeros[1000][6];
string nombre, ncuenta, contrasena, ruta, bus, hora;
int fila=0, pos=0, n_pasajero = 1, n_ruta, hr, as_seleccionado, llenos;

class design{
	public:
		void gotoxy(int x, int y);
		static void SetColor(int ForgC);
		void cursor(bool showFlag);
		void menu();
		void registro();
		void cargando();
		void s_ticket();
	protected:
		
};

class menus{
	public:
		int gotoxy(USHORT x,USHORT y);
		void menu_principal();
		void menu_pasajero();
		int menu(const char titulo[], const char *opciones[], int n);		
	protected:
};

menus m;
design d;

void llenar_asientos(){
	for(int i=1; i < 21; i++)
		asientos[i]=i;
}
void revisar_asientos(){
	llenos = 0;
	const char* as;
	int n_as;
	llenar_asientos();
		for(int i = 0; i < n_pasajero;i++){
		if(pasajeros[i][5]!="Cancelado"){
		as = pasajeros[i][4].data();
		n_as= atoi(as);
		if(bus==pasajeros[i][1] && ruta==pasajeros[i][2]  && hora==pasajeros[i][3]){
			asientos[n_as]=0;
			llenos++;
				}
			}
		}
	}	
void reservar(){
 std::cin.exceptions(std::ios_base::failbit);
	try
  {				rt1:
  				system("cls");
				d.gotoxy(40,2);cout<<"Reservando asiento - "<<usuarios[pos][0];
				d.gotoxy(5,5);printf("Destinos disponibles: ");
				for(int i = 1; i < 7; i++){d.gotoxy(8,5+i);cout<<i<<") "<<buses[i][1];}
				d.cursor(true);
				d.gotoxy(5,12);printf("Escriba el numero de la ruta en la cual desea viajar: ");
				d.gotoxy(59,12);std::cin>>n_ruta;
				if(n_ruta < 1 || n_ruta >6)goto rt1;
				bus =  buses[n_ruta][0];
				ruta = buses[n_ruta][1];
				
				rt2:
				system("cls");
			 	d.gotoxy(40,2);cout<<"Reservando asiento - "<<usuarios[pos][0];
			 	d.gotoxy(5,4);cout<<"Ha seleccionado viajar hacia "<<ruta<<" el bus diponible es "<<bus;
			 	d.gotoxy(5,6);printf("Seleccione el horario: \n 	1) Mañana \n 	2) Tarde \n 	3) Noche");
			 	d.gotoxy(5,11);printf("Escriba el numero de horario: ");
			 	d.gotoxy(35,11);std::cin>>hr;
			 	
			 	if(hr < 1 || hr > 3)goto rt2;
				hora = horarios[hr];
				
				rt3:
				system("cls");	
				revisar_asientos();
				if(llenos == 20){
					d.gotoxy(5,12);printf("Todos los asientos estan llenos seleccione otro horario.");	
					Sleep(3000);
				}else{
				
				d.gotoxy(40,2);cout<<"Reservando asiento - "<<usuarios[pos][0];
				d.gotoxy(5,4);cout<<"Ha seleccionado viajar hacia "<<ruta<<" el bus diponible es "<<bus<<" en horario "<<hora<<endl;
				
				d.gotoxy(5,6);printf("Asientos disponibles: ");
				d.gotoxy(5,7);for(int i = 1; i < 21;i++)
				if( asientos[i]!=0)cout<<asientos[i]<<"|";
				
				d.gotoxy(5,10);printf("Ingrese el asiento que desea reservar: ");
				d.gotoxy(44,10);cin>>as_seleccionado;
				
				if(as_seleccionado < 1 || as_seleccionado > 20)goto rt3;
				
				if(asientos[as_seleccionado]==0){
					d.gotoxy(5,12);printf("El asiento que ingreso esta reservado. Seleccione otro!");
					Sleep(2000);
					goto rt3;
				}
					n_pasajero++;
					ostringstream convertir;
					convertir << as_seleccionado;
						pasajeros[n_pasajero-1][0]=ncuenta;
						pasajeros[n_pasajero-1][1]=bus;
						pasajeros[n_pasajero-1][2]=ruta;
						pasajeros[n_pasajero-1][3]=hora;
						pasajeros[n_pasajero-1][4]=convertir.str();	
						pasajeros[n_pasajero-1][5]="Reservado";
						d.gotoxy(5,12);printf("El asiento ha sido reservado exitosamente!");
						Sleep(2000);		
			}
		}catch (const std::ios_base::failure ){
		std::cin.clear();
		d.gotoxy(5,18);printf("Solo se permite ingresar valores numericos. Presione Enter para continuar.");	
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		Sleep(150);
		}
	}
	
void confirmar_reserva(){
	system("cls");
	int p=0, cont=0 , n=0;
	string line(84,'-');
	string YN;
	for(int l=1;l<n_pasajero;l++)
	if(ncuenta==pasajeros[l][0] && pasajeros[l][5]!="Cancelado")cont++;
	if(cont == 0){
	d.gotoxy(5,4);cout<<"Nota: No ha reservado ningun asiento."<<endl;	
	Sleep(2000);	
	}else{
	d.gotoxy(40,2);cout<<"** Confirmando los asientos reservados **";
	d.gotoxy(5,4);cout<<"Nota: Si un asiento es cancelado tendra que volver a crear la reserva."<<endl;	
	d.gotoxy(5,6);cout<<"Nombre :"<<usuarios[pos][0]<<endl;
	d.gotoxy(5,7);cout<<line<<endl;
	d.gotoxy(5,8);cout<<"|No. |Bus		|Ruta		|Horario	|Asiento	|Estado		|"<<endl;
	d.gotoxy(5,9);cout<<line<<endl;
	for(int x=1;x<n_pasajero;x++){
	if(ncuenta==pasajeros[x][0] && pasajeros[x][5]!="Cancelado"){
		p++;
		d.gotoxy(5,9+p); cout<<"|"<<p; 
		d.gotoxy(10,9+p);cout<<"|"<<pasajeros[x][1];
		d.gotoxy(24,9+p);cout<<"|"<<pasajeros[x][2];
		d.gotoxy(40,9+p);cout<<"|"<<pasajeros[x][3];
		d.gotoxy(56,9+p);cout<<"|"<<pasajeros[x][4];
		d.gotoxy(72,9+p);cout<<"|"<<pasajeros[x][5];
		d.gotoxy(88,9+p);cout<<"|";
				}
			}		
		d.gotoxy(5,9+p+1);cout<<line<<endl;
		}
		for(int j=1;j<n_pasajero;j++){
			if(ncuenta==pasajeros[j][0] && pasajeros[j][5]!="Cancelado"){
			d.gotoxy(5,9+p+2);cout<<"Ingrese Y/N para confirmar o cancelar la reservacion. "<<endl;	
			n++;
			if(pasajeros[j][5]!="Reservado"){
			d.gotoxy(5,9+p+2+n);cout<<"No. "<<n<<" - Y/N: Confirmado";	
			}else{
			d.gotoxy(5,9+p+2+n);cout<<"No. "<<n<<" - Y/N: ";
			d.gotoxy(18,9+p+2+n);cin>>YN;
			if(YN=="Y" || YN == "y"){
				pasajeros[j][5]="Confirmado";
			}else if(YN=="N" || YN == "n"){
				pasajeros[j][5]="Cancelado";
				}else{
			d.gotoxy(20,9+p+2+n);cout<<", Lo que ingreso es invalido.";
			Sleep(1000);		
						}
					}
				}
			}		
			cout<<endl;
			system("pause");
		}
void cancelar_reserva(){
	system("cls");
	int p=0, cont=0 , n=0;
	string line(84,'-');
	string YN;
	for(int l=1;l<n_pasajero;l++)
	if(ncuenta==pasajeros[l][0] && pasajeros[l][5]!="Cancelado")cont++;

	if(cont == 0){
		
	d.gotoxy(5,4);cout<<"Nota: No ha reservado ningun asiento."<<endl;	
	Sleep(2000);	
	}else{
	d.gotoxy(40,2);cout<<"** Cancelando los asientos reservados o confirmados**";
	d.gotoxy(5,4);cout<<"Nota: Si un asiento es cancelado tendra que volver a crear la reserva."<<endl;	
	d.gotoxy(5,6);cout<<"Nombre :"<<usuarios[pos][0]<<endl;
	d.gotoxy(5,7);cout<<line<<endl;
	d.gotoxy(5,8);cout<<"|No. |Bus		|Ruta		|Horario	|Asiento	|Estado		|"<<endl;
	d.gotoxy(5,9);cout<<line<<endl;
	for(int x=1;x<n_pasajero;x++){
	if(ncuenta==pasajeros[x][0] && pasajeros[x][5]!="Cancelado"){
		p++;
		d.gotoxy(5,9+p); cout<<"|"<<p; 
		d.gotoxy(10,9+p);cout<<"|"<<pasajeros[x][1];
		d.gotoxy(24,9+p);cout<<"|"<<pasajeros[x][2];
		d.gotoxy(40,9+p);cout<<"|"<<pasajeros[x][3];
		d.gotoxy(56,9+p);cout<<"|"<<pasajeros[x][4];
		d.gotoxy(72,9+p);cout<<"|"<<pasajeros[x][5];
		d.gotoxy(88,9+p);cout<<"|";
				}
			}		
		d.gotoxy(5,9+p+1);cout<<line<<endl;
		}
		for(int j=1;j<n_pasajero;j++){	
			if(ncuenta==pasajeros[j][0] && pasajeros[j][5]!="Cancelado"){
			d.gotoxy(5,9+p+2);cout<<"Ingrese Y/N para cancelar la reservacion del asiento. "<<endl;	
			n++;
			d.gotoxy(5,9+p+2+n);cout<<"No. "<<n<<" - Y/N: ";
			d.gotoxy(18,9+p+2+n);cin>>YN;
			if(YN=="Y" || YN == "y"){
				pasajeros[j][5]="Cancelado";
			}else if(YN=="N" || YN == "n"){
				}else{
			d.gotoxy(20,9+p+2+n);cout<<"Lo que ingreso es invalido.";
			Sleep(1000);		
						}
				}
			}		
			cout<<endl;
			system("pause");
		}
void imprimir_ticket(){
	int s, cont;
	
	s=0;
	cont=0;
	
	d.gotoxy(25,2);cout<<"** Lista de tickets creados **";
	d.gotoxy(5,3);cout<<"Gracias por preferir nuestro sistema control de rutas.";
	d.gotoxy(5,5);cout<<"Nombre :"<<usuarios[pos][0];
	for(int i=1; i < n_pasajero;i++){
		
		if(ncuenta==pasajeros[i][0] ){
		cont++;	
		d.gotoxy(5,6+i+s);cout<<"Tiket #"<<cont;	
		d.gotoxy(5,6+i+1+s);cout<<"------------------------------";	
		d.gotoxy(5,6+i+2+s);cout<<"Bus        : "<<pasajeros[i][1];
		d.gotoxy(5,6+i+3+s);cout<<"Ruta       : "<<pasajeros[i][2];
		d.gotoxy(5,6+i+4+s);cout<<"Horario    : "<<pasajeros[i][3];
		d.gotoxy(5,6+i+5+s);cout<<"No. Asiento: "<<pasajeros[i][4];
		d.gotoxy(5,6+i+6+s);cout<<"Estado     : "<<pasajeros[i][5];	
		d.gotoxy(5,6+i+7+s);cout<<endl;
		s = 8*cont;
				}	
			}
			system("pause");	
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
				  	gotoxy(20, 1); cout << titulo;
				  	gotoxy(10, 2);cout<<"No se permite dentro de la unidad: fumar, gritar, uso de armas.";
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
		         	cin.ignore();
		            break;
		         case 2:
		         	system("cls");
		         	confirmar_reserva();
		         	cin.ignore();
		            break;
		         case 3:
		         	system("cls");
		         	cancelar_reserva();
		         	cin.ignore();
		            break;
				 case 4:
		         	system("cls");
		         	imprimir_ticket();
		         	cin.ignore();
		            break;	   
		         case 5:
		            cout << "\nVolviendo al menu principal. Muchas gracias!" << endl;
		            repite = false;
		            d.cursor(false);
		            m.menu_principal();
		            Sleep(2000);
		            cin.ignore();
		            cin.clear();
		            break;
		      }
		   } while(repite);
		}
		
		void design::gotoxy(int x,int y){  
      	HANDLE hcon;  
      	hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      	COORD dwPos;  
      	dwPos.X = x;  
      	dwPos.Y= y;  
      	SetConsoleCursorPosition(hcon,dwPos);  
 	} 
	void design::SetColor(int ForgC){
 		WORD wColor;
  		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  		CONSOLE_SCREEN_BUFFER_INFO csbi;

    	//We use csbi for the wAttributes word.
 		if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 		{	
        //Mask out all but the background attribute, and add in the forgournd color
      		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      		SetConsoleTextAttribute(hStdOut, wColor);
 			}
				}		
void design::cursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}
void design::menu(){
	gotoxy(20,2);
	SetColor(15);
	printf("** AUTENTICACION UNICA **");
}
void design::registro(){
	SetColor(15);
	gotoxy(20,2);printf("** CREAR UNA NUEVA CUENTA **");	
}
void design::cargando(){
	cursor(false);
	SetColor(15);
	gotoxy(5,9);printf("Ingresando al sistema.");
	Sleep(1000);
	gotoxy(27,9);printf(".");
	Sleep(1000);
	gotoxy(28,9);printf(".");
	Sleep(1000);
	gotoxy(29,9);printf(".");
	Sleep(1000);		
}
int main(int argc, char** argv) {
	
		pasajeros[0][0]="admin";
		pasajeros[0][1]="Bus No. 0001";
		pasajeros[0][2]="Villanueva";
		pasajeros[0][3]="06:00 AM";
		pasajeros[0][4]="12";	
		pasajeros[0][5]="Cancelado";	
		
		usuarios[0][0]="Admininistrador";
		usuarios[0][1]="admin";
		usuarios[0][2]="admin";
				
		buses[1][0]="Bus No. 0001";
		buses[1][1]="Villanueva";
		
		buses[2][0]="Bus No. 0002";
		buses[2][1]="Cortes";
		
		buses[3][0]="Bus No. 0003";
		buses[3][1]="Progreso";
		
		buses[4][0]="Bus No. 0004";
		buses[4][1]="Centro";
		
		buses[5][0]="Bus No. 0005";
		buses[5][1]="Barbara";
		
		buses[6][0]="Bus No. 0006";
		buses[6][1]="Sede Norte";
		
		horarios[1]="Mañana";
		horarios[2]="Tarde";
		horarios[3]="Noche";
				
	m.menu_principal();
	
		return 0;
	}	
			
