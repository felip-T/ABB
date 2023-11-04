# Árvore binária de busca
O código é composto pelos arquivos abb.h, sdb.h e main.cpp. Adicionalmente, um arquivo Makefile com instruções para compilação em linux (GCC) foi implementado. O arquivo pessoas.txt é utilizado para ler dados. O repositório possuí também um arquivo "output.txt", com a saída do programa.

# abb.h
Arquivo com a implementação da árvore binária de busca. A implementação contém as seguintes funções.

- Contrutor padrão

Atribuí nullptr para o ponteiro responsável por armazenar o dado.
```cpp
    ABB()
```

- Construtor recebendo dado como argumento

Atribuí o armazena o argumento.
```cpp
    ABB(T)
```

- Construtor de cópia
```cpp
    ABB(const ABB<T>&)
```

- Construtor recebendo iterator como argumento

Adiciona cada elemento à árvore.
```cpp
    template <class iterator> ABB(iterator begin, iterator end)
```

- Varredura preorder

Varre a árvore em preorder aplicando uma função em cada nó.
```cpp
    void preorder(std::function<void(ABB<T> *)> func = [](T &d) {}) 
```
- Varredura inorder

Varre a árvore em inorder aplicando uma função em cada nó.
```cpp
    void inorder(std::function<void(ABB<T> *)> func = [](T &d) {}) 
```

- Varredura posorder

Varre a árvore em posorder aplicando uma função em cada nó.
```cpp
    void posorder(std::function<void(ABB<T> *)> func = [](T &d) {}) 
```

- Inserção

Recebe o dado e, opcionalmente, uma função para realizar a comparação.
```cpp
  void insert(T, std::function<bool(T &, T &)> = std::less<T>(), std::function<bool(T &, T &)> = std::greater<T>())
```

- Busca

Recebe um argmento e, opcionalmente, uma função para ser aplicada ao dado, retornando o mesmo tipo do argumento. A função deve ter o mesmo critério de ordenação da inserção. Retorna a sub-árvore correspondente.
```cpp
  ABB<T> *search(U, std::function<U(T &)> = [](T &d) { return d; })
```

- getData

Retorna o dado
```cpp
    getData()
```

Obs: não é necessário destrutor especializado pois todos a memória é gerenciada a partir de unique_ptrs.

# sdb.h
Função de testes para a ABB, implementa a classe Pessoa e a classe sdb.

Funções da sdb:
- inserir elemento
```cpp
    void insert(T add)
```

- busca na edl

Busca pelo índice no vector, retorna o elemento.
```cpp
    T searchEdl(unsigned idx)
```

- busca na abb

Busca pela chave na abb, retorna o índice no vector.
```cpp
    unsigned searchKey(key k)
```

- busca

Faz searchEdl e searchKey em sequência.
```cpp
    T search(key k) 
```

- remoção

Remove elemento pela chave, o elemento só é removido na abb e o índice desse elemento é adicionado a um outro vector, indicando que esse índice está disponível em uma nova inserção.
```cpp
  void remove(key k)
```

- Função para retornar chave

Ensina a sdl como obter a chave de um elemento. Necessário para fazer inserções.
```cpp
	void setKey(std::function<key(T &)> f)
```

- ordenação

Ordena a edl, cria um novo vector ordenado, sem espaços deletados e substituí o vector antigo. Essa função exibe o vector ordenado na tela, para demostração.
```cpp
	void order(){
```
