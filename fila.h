struct Values{
  double (*func) (double);
  double limiteA;
  double limiteB;
  double erro;
  double integral;
  double funcEmA;
  double funcEmB;
  double funcEmMedio;
  struct Values * next;
};
  
// The fila, front stores the front node of LL and rear stores the 
// last node of LL 
typedef struct { 
    struct Values *front, *rear;
    long long int size;
} fila;
  
// A utility function to create a new linked list node. 
struct Values* novoNo(double (*func) (double), double limA, double limB, double erro, double integral, double funcEmA, double funcEmB, double funcEmMedio) 
{ 
    struct Values* value = (struct Values*) malloc (sizeof(struct Values)); 
    value->func = func;
    value->limiteA = limA;
    value->limiteB = limB;
    value->erro = erro;
    value->integral = integral;
    value->funcEmA = funcEmA;
    value->funcEmB = funcEmB;
    value->funcEmMedio = funcEmMedio;
    value->next = NULL; 
    return value; 
} 
  
// A utility function to create an empty fila 
fila* criaFila() 
{ 
    fila* q = (fila*) malloc (sizeof(fila)); 
    q->front = q->rear = NULL;
    q->size = 0;
    return q; 
} 
  
// The function to add a key k to q 
void enfila(fila* q, double (*func) (double), double limA, double limB, double erro, double integral, double funcEmA, double funcEmB, double funcEmMedio) 
{ 
    // Create a new LL node 
    struct Values* temp = novoNo(func, limA, limB, erro, integral, funcEmA, funcEmB, funcEmMedio); 
  
    // If fila is empty, then new node is front and rear both 
    if (q->rear == NULL) { 
        q->front = q->rear = temp;
        q->size++;
        return; 
    } 
  
    // Add the new node at the end of fila and change rear 
    q->rear->next = temp; 
    q->rear = temp;
    q->size++;
} 
  
// Function to remove a key from given fila q 
struct Values* defila(fila* q) 
{ 
    // If fila is empty, return NULL. 
    if (q->front == NULL) 
        return NULL; 
  
    // Store previous front and move front one node ahead 
    struct Values* temp = q->front; 
    //free(temp); 
  
    q->front = q->front->next; 
  
    // If front becomes NULL, then change rear also as NULL 
    if (q->front == NULL) 
        q->rear = NULL;
    
    q->size--;

    return temp; 
} 