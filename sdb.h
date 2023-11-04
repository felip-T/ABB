#ifndef SDB_H
#define SDB_H

#include "abb.h"
#include <string>
#include <tuple>
#include <vector>
#include <iostream>
#include <functional>

class Pessoa {
public:
  std::string nome;
  unsigned long cpf;
  std::string dataNascimento;

  bool operator<(const Pessoa &p) const { return this->nome < p.nome; }
  bool operator>(const Pessoa &p) const { return this->nome > p.nome; }
  bool operator==(const Pessoa &p) const { return this->nome == p.nome; }
	
	friend std::ostream& operator<<(std::ostream& os, const Pessoa& p) {
		os << p.nome << " " << p.cpf << " " << p.dataNascimento;
		return os;
	}
};

template <class T, class key> class SDB {
public:
  size_t pos;
  void insert(T add) {
    if (removed.empty()) {
      edl.push_back(add);
      pos = edl.size() - 1;
    } else {
      pos = removed.back();
      edl.at(pos) = add;
      removed.pop_back();
    }
    std::tuple<unsigned, key> t =
        std::make_tuple<unsigned, key>(pos, getKey(add));

    auto l = [](std::tuple<unsigned, key> &a, std::tuple<unsigned, key> &b) {
      return std::get<1>(a) < std::get<1>(b);
    };
    auto g = [](std::tuple<unsigned, key> &a, std::tuple<unsigned, key> &b) {
      return std::get<1>(a) > std::get<1>(b);
    };

    ab.insert(t, l, g);
  }

  T searchEdl(unsigned idx) { return edl.at(idx); }

  void remove(key k) {
    removed.push_back(searchKey(k));
    std::function<key(std::tuple<unsigned, key> &)> f =
        [](std::tuple<unsigned, key> &d) -> key { return std::get<1>(d); };
    ab.remove(k, f);
  }

	T search(key k) {return edl.at(searchKey(k));}

  unsigned searchKey(key k) {
    std::function<key(std::tuple<unsigned, key> &)> f =
        [](std::tuple<unsigned, key> &d) -> key { return std::get<1>(d); };

    return std::get<0>(ab.search(k, f)->getData());
  }

	void setKey(std::function<key(T &)> f) { getKey = f; }

	void order(){
		std::vector<T> vec;
		ab.inorder([&vec, this](ABB<std::tuple<unsigned, key>> *d){
			vec.push_back(edl.at(std::get<0>(d->getData())));
		});
		for (auto& v : vec) {
			std::cout << v << std::endl;
		}
		edl = vec;
		removed.clear();
	}

private:
  ABB<std::tuple<unsigned, key>> ab;
  std::function<key(T &)> getKey;
  std::vector<T> edl;
  std::vector<size_t> removed;
};

#endif
