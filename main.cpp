#include "abb.h"
#include "sdb.h"
#include <functional>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

int main() {

	SDB<Pessoa, std::string> sdb;
	auto getNome = [](Pessoa& p) ->std::string { return p.nome; };
	std::vector<std::string> nomes;

	sdb.setKey(getNome);

	std::ifstream file("pessoas.txt");
	std::string aux;
	while (std::getline(file, aux)) {
		Pessoa p;
		std::stringstream ss(aux);
		ss >> p.nome;
		nomes.push_back(p.nome);
		ss >> p.cpf;
		ss >> p.dataNascimento;
		sdb.insert(p);
	}

	for (auto& n : nomes) {
		std::cout << sdb.search(n) << " indice-> " << sdb.searchKey(n) << std::endl;
	}

	sdb.remove("Ana");
	sdb.remove("Felipe");
	
	Pessoa p1;
	p1.nome = "Isa";
	p1.cpf = 123456789;
	p1.dataNascimento = "20/01/2000";
	sdb.insert(p1);
	nomes.push_back(p1.nome);

	p1.nome = "Alexandre";
	p1.cpf = 12345678950;
	p1.dataNascimento = "28/01/2000";
	sdb.insert(p1);
	nomes.push_back(p1.nome);

	p1.nome = "Lucas";
	p1.cpf = 123478950;
	p1.dataNascimento = "30/01/2000";
	sdb.insert(p1);
	nomes.push_back(p1.nome);

	std::cout << std::endl;

	for (auto& n : nomes) {
		try{
			std::cout << sdb.search(n) << " indice-> " << sdb.searchKey(n) << std::endl;
		}
		catch (...) {
			std::cout << "Nome não encontrado: " << n << std::endl;
		}
	}

	std::cout << std::endl;

	sdb.order();

  return 0;
}
