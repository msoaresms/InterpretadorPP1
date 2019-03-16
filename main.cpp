#include <iostream>
using namespace std;
//------------------------------------------------------------------------
class Item {
private:
    string linha;
public:
    Item() {}
    Item(string pLinha) { this->linha = pLinha; }

    string getLinha() { return this->linha; }
    void setLinha(string pLinha) { this->linha = pLinha; }

    void print();
    bool igual(string);
};
//------------------------------------------------------------------------
template <class T>
class No {
private:
    T item;
    No<T> * prox;
public:
    T getItem() { return this->item; }
    void setItem(T pItem) { this->item = pItem; }
    No<T> * getProx() { return this->prox; }
    void setProx(No<T> * pProx) { this->prox = pProx; }
};
//------------------------------------------------------------------------
template <class T>
class Pilha {
private:
    No<T> * topo, * fundo;
public:
    Pilha() {
        this->fundo = new No<T>();
        this->fundo->setProx(NULL);
        this->topo = this->fundo;
    }

    No<T> * getTopo() { return this->topo; }
    void setTopo(No<T> * pTopo) { this->topo = pTopo; }
    No<T> * getFundo() { return this->fundo; }
    void setFundo(No<T> * pFundo) { this->fundo = pFundo; }

    void empilha(T);
    void desempilha(T *);
    bool vazia();
};
//------------------------------------------------------------------------
template <typename T>
class Lista {
private:
    T * item;
    int TAM;
    int n;
    bool vazia();
    bool posicaoValida(int);
public:
    Lista(int tam) {
        this->n = 0;
        this->TAM = tam;
        this->item = new T[TAM];
    }
    void insere(T);
    void print();
    string busca(int);
    int busca(string);
    void remove(int, T &);
};
//------------------------------------------------------------------------
template <typename T>
void Pilha<T>::empilha(T pItem) {
    No<T> * aux = new No<T>();
    this->topo->setItem(pItem);
    aux->setProx(this->topo);
    this->topo = aux;
}
template <typename T>
void Pilha<T>::desempilha(T * x) {
    if (!this->vazia()) {
        No<T> * aux = this->topo;
        this->topo = this->topo->getProx();
        * x = this->topo->getItem();
        delete aux;
    }
}
template <typename T>
bool Pilha<T>::vazia() {
    return (this->topo == this->fundo);
}
//------------------------------------------------------------------------
template <typename T>
void Lista<T>::insere(T x) {
    if (n < TAM) {
        //n++;
        item[n] = x;
        n++;
    }
    else {
        cout << "LISTA CHEIA" << endl;
    }
}
template <typename T>
void Lista<T>::remove(int pos, T &t) {
    if (!vazia() && posicaoValida(pos)) {
        t = item[pos];
        for (int i = pos; i < n; i++) {
            item[i] = item[i + 1];
        }
        n--;
    }
    else { cout << "LISTA VAZIA OU POSIÇÃO INVÁLIDA" << endl; }
}
template <typename T>
string Lista<T>::busca(int pos) {
    string pAux;
    Item pItem;
    if (!vazia() && posicaoValida(pos)) {
        pItem = item[pos];
        pAux = pItem.getLinha();
        return pAux;
    }
    else { return ("LISTA VAZIA OU POSIÇÃO INVÁLIDA"); }
}
template <typename T>
int Lista<T>::busca(string pAux) {
    if (!vazia()){
        Item x;
        for (int i = 0; i < n; i++){
            x = item[i];
            if (x.igual(pAux)){
                return i;
            }
        }
    }
    return -1;
}
template <typename T>
void Lista<T>::print() {
    for (int i = 0; i < n; i++)  { item[i].print(); }
}
template <typename T>
bool Lista<T>::vazia() { return (n == 0); }
template <typename T>
bool Lista<T>::posicaoValida(int pos) { return (1 <= pos && pos <= n); }
//------------------------------------------------------------------------
void Item::print() { cout << this->linha << endl; }
bool Item::igual(string pTeste){
    int i = 0;
    while (pTeste[i] != '\0'){
        i++;
    }
    for (int j = 0; j < i; j++){
        if (this->linha[j] != pTeste[j] ){
            return false;
        }
    }
    return true;
}
//------------------------------------------------------------------------
//Função para calcular o número de caracteres em cada linha da entrada
int tamanho(string pLinha) {
    int i = 0;
    while (pLinha[i] != '\0'){
        i++;
    }
    return i;
}
//------------------------------------------------------------------------
int main(int argc, const char * argv[]) {
    Lista<Item> entrada(250); //Guarda as linhas da entrada
    Pilha<int> funcao;        //Guarda as linhas nos chamamentos de funções
    string sAux = "";         //String auxiliar
    string saida = "";        //String que guarda a saída do intepretador
    string linha = "";        //String usanda para capturar cada linha da entrada
    int tam;                  //Usada para guardar o tamanho de cada linha
    int numLinha;             //Usada para se guardar a linha que está sendo computada
    bool naoFim = true;       //Auxilia no encerramento da execução

    while(getline(cin, sAux) && sAux.compare("~")){
        Item linhaEntrada(sAux);
        entrada.insere(linhaEntrada);
    }

    numLinha = entrada.busca("Z :");
    while (naoFim) {
        numLinha++;
        linha = entrada.busca(numLinha);
        tam = tamanho(linha);
        tam--;
        if (tam == 11) {
            saida += linha[10];
            saida += ' ';
//            cout << "THE CAKE IS A LIE 1" << endl;
        } else if (tam == 12) {
            saida += linha[10];
            saida += linha[11];
            saida += ' ';
//           cout << "THE CAKE IS A LIE 2" << endl;
        } else if (tam == 5) {
            funcao.empilha(numLinha);
            sAux = linha[4];
            sAux += " :";
            numLinha = entrada.busca(sAux);
//            cout << "THE CAKE IS A LIE 3" << endl;
        } else {
            if (funcao.vazia()) {
                naoFim = false;
            } else {
                funcao.desempilha(&numLinha);
            }
//            cout << "THE CAKE IS A LIE 4" << endl;
        }
    }

    cout << saida;

    return 0;
}