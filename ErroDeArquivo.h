#ifndef ERRODEARQUIVO_H
#define ERRODEARQUIVO_H
#include <string>
#include <stdexcept>

using namespace std;

class ErroDeArquivo : public logic_error
{
    public:
        ErroDeArquivo(string mensagem);
        virtual ~ErroDeArquivo();

    protected:

    private:
        string mensagem;
};

#endif // ERRODEARQUIVO_H
