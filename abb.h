#ifndef ABB_H
#define ABB_H

#include <iostream>
#include <functional>
#include <memory>

template <class T> class ABB {
public:
  ABB();
	ABB(T);
	ABB(const ABB<T>&);
  template <class iterator> ABB(iterator, iterator);
  void insert(T, std::function<bool(T &, T &)> = std::less<T>(),
              std::function<bool(T &, T &)> = std::greater<T>());
  template <class U>
  ABB<T> *search(
      U, std::function<U(T &)> = [](T &d) { return d; });

  void preorder(std::function<void(ABB<T> *)> func = [](T &d) {}) {
    pre(func, this);
  }
  void posorder(std::function<void(ABB<T> *)> func = [](T &d) {}) {
    pos(func, this);
  }
  void inorder(std::function<void(ABB<T> *)> func = [](T &d) {}) {
    in(func, this);
  }

	template <class U>
	void remove(U, std::function<U(T &)> = [](T &d) { return d; });

	T getData();

private:
  void pre(std::function<void(ABB<T>*)> func, ABB<T>* here);
  void in(std::function<void(ABB<T>*)> func, ABB<T>* here);
  void pos(std::function<void(ABB<T>*)> func, ABB<T>* here);
	std::unique_ptr<ABB<T>> removeNode(std::unique_ptr<ABB<T>>);
	std::unique_ptr<T> data;
	std::unique_ptr<ABB<T>> left;
	std::unique_ptr<ABB<T>> right;
};

template <class T> ABB<T>::ABB() : data(nullptr) {}

template <class T> ABB<T>::ABB(T _data) : data(std::make_unique<T>(_data)) {}

template <class T> ABB<T>::ABB(const ABB<T>& other) {
	data = std::make_unique<T>(*other.data);
	if (other.left) {
		left = std::make_unique<ABB<T>>(*other.left);
	}
	if (other.right) {
		right = std::make_unique<ABB<T>>(*other.right);
	}
}

template <class T>
template <class iterator>
ABB<T>::ABB(iterator begin, iterator end) {
	data = std::make_unique<T>(*(begin++));
  while (begin != end) {
    insert(*(begin++));
  }
}

template <class T> void ABB<T>::insert(T _data, std::function<bool(T&,T&)> less, std::function<bool(T&,T&)>greater) {
	if (data == nullptr) { data = std::make_unique<T>(_data); return; }
  if (less(_data, *data)) {
    if (left == nullptr) {
      left = std::make_unique<ABB<T>>(_data);
    } else {
      left->insert(_data, less, greater);
    }
  } else {
		if (greater(_data, *data)) {
    	if (right == nullptr) {
      	right = std::make_unique<ABB<T>>(_data);
    	} else {
      	right->insert(_data, less, greater);
    	}
  	}
	}
}

template <class T>
template <class U>
ABB<T> *ABB<T>::search(U _data, std::function<U(T &)> func) {
	if (data == nullptr) {throw 1;}
  if (_data < func(*data)) {
    if (left == nullptr)
      throw 1;
    return left->search(_data, func);
  }
  if (_data > func(*data)) {
    if (right == nullptr)
      throw 1;
    return right->search(_data, func);
  }
  return this;
}

template <class T>
void ABB<T>::pre(std::function<void(ABB<T>*)> func, ABB<T>* here) {
  if (here == nullptr)
    return;
  func(here);
	if (here->left)
  	pre(func, here->left.get());
	if (here->right)
  	pre(func, here->right.get());
}

template <class T>
void ABB<T>::in(std::function<void(ABB<T>*)> func, ABB<T>* here) {
  if (here == nullptr)
    return;
  in(func, here->left.get());
  func(here);
  in(func, here->right.get());
}

template <class T>
void ABB<T>::pos(std::function<void(ABB<T>*)> func, ABB<T>* here) {
  if (here)
    return;
  pos(func, here->left.get());
  pos(func, here->right.get());
  func(here);
}

template <class T>
template <class U>
void ABB<T>::remove(U _data, std::function<U(T &)> func) {
    if (!data) {
        return;
    }
    
    U currentData = func(*data);
    
    if (_data < currentData) {
        if (left) {
            if (func(*left->data) == _data) {
                left = removeNode(std::move(left));
            } else {
                left->remove(_data, func);
            }
        }
    } else if (_data > currentData) {
        if (right) {
            if (func(*right->data) == _data) {
                right = removeNode(std::move(right));
            } else {
                right->remove(_data, func);
            }
        }
		} else if (_data == currentData) {
			//Quando o nó é a raiz
			//Criei um unique_ptr auxiliar pra passar pra função de removeNode
			//Depois destroquei os valores com o objeto atual
			auto aux = std::make_unique<ABB<T>>();
			aux->data = std::move(data);
			aux->left = std::move(left);
			aux->right = std::move(right);
			aux = removeNode(std::move(aux));
			data = std::move(aux->data);
			left = std::move(aux->left);
			right = std::move(aux->right);
		}
}

template <class T>
std::unique_ptr<ABB<T>> ABB<T>::removeNode(std::unique_ptr<ABB<T>> node) {
    if (!node) {
        return nullptr;
    }
    
    if (!node->left) {
        return std::move(node->right);
    } else if (!node->right) {
        return std::move(node->left);
    } else {
        std::unique_ptr<ABB<T>> successor = std::move(node->right);
        ABB<T> *successorPtr = successor.get();
        while (successorPtr->left) {
            successorPtr = successorPtr->left.get();
        }
        successorPtr->left = std::move(node->left);
        return successor;
    }
}

template <class T> T ABB<T>::getData() { return *data; }

#endif
