#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int tama; // n elementos leidos
string nombreArchivo = "cartas_5";

//Funcion que elimina tarjeta (ordena)
pair<int, vector<int>> eliminarTarjetas(const vector<int>&); //  deuvelve: min_tarjetas elimnadas & vector ordenado
// Funcion que lee archivo
pair<bool, vector<int>> obtenerDatos(); // Devuelve: si pudo leer y el vector con los datos

int main() {
  vector<int> tarjetas = obtenerDatos().second; // Leer archivo
  ofstream results(nombreArchivo + ".out", ios::trunc); // Crear archivo de salida

  auto tarjetasOrdenado = eliminarTarjetas(tarjetas); // Obtener el vector ordenado y el min eliminaciones
  results << tarjetas.size() - tarjetasOrdenado.first << endl; // Guarda en archivo el tamaño de tarjetas ordenadas

  cout << "Se deben eliminar " << tarjetasOrdenado.first // Imprime cuantas deben eliminarse
       << " tarjetas para que queden ordenadas." << endl << endl;
  cout << "Tarjetas ordenadas: " << endl;
  for (int tar : tarjetasOrdenado.second) { // Imprime indices de tarjetas ordenadas
    results << tar << endl;
    cout << tar << endl;
  }
  cout << endl;

  system("pause");
  return 0;
}

pair<int, vector<int>> eliminarTarjetas(const vector<int>& tarjetas) {
  int n = tama; // Numero de elementos

  vector<int> lis(n, 0); // Crear Lista llena de n ceros

  for (int i = 1; i < n; ++i) { // Iteracion de 0 a n
    for (int j = 0; j < i; ++j) { // Iteracion de 0 a i
      if (tarjetas[i] > tarjetas[j] && lis[i] < lis[j] + 1) { // Si las tarjetas anteriores son menores que la actual y la posicion de la lista es menor
        lis[i] = lis[j] + 1; //incrementar el peso
      }
    }
  }

  int max_length = *max_element(lis.begin(), lis.end()); // Busca el elemento mayor en la lista

  vector<int> subsequence_cards; // Crea vector ordenado
  for (int i = n - 1; i >= 0; --i) { // Desde el ultimo elemento al primero
    if (lis[i] == max_length) { // Si corresponde al mayor
      subsequence_cards.insert(subsequence_cards.begin(), i+1); // Lo guarda
      max_length--; // Decrementa el mayor
    }
  }

  int min_deletions = n - subsequence_cards.size(); // Guarda el minimo de eliminaciones

  return make_pair(min_deletions, subsequence_cards); // Devuelve los datos
}

pair<bool, vector<int>> obtenerDatos() {
  vector<int> data;
  ifstream tarjetas(nombreArchivo + ".txt"); // Abre el archivo
  string linea;
  int num;

  if (!tarjetas) { // Si no existe el archivo
    cout << "Archivo inexistente!" << endl;
    return make_pair(false, data);
  } else { // Si existe el archivo
    getline(tarjetas, linea); // Lee linea por linea
    istringstream iss(linea); // Conversion numerica
    iss >> tama; // Primer elemento leido corresponde al numero de elementos
    while (getline(tarjetas, linea)) { // Repeticion ciclica para leer cada elemento
      // Convierte la línea a un flujo de entrada stringstream
      istringstream iss(linea);

      if (iss >> num) {  // Intenta hacer la lectura
        data.push_back(num);
      } else { // Si no es numerico devuelve falso
        cout << "Entrada de datos no numerica" << endl;
        return make_pair(false, data);
      }
    }
  }

  tarjetas.close(); // Cerrar archivo
  return make_pair(true, data); // Devolver datos
}