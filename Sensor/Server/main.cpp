#include <cppwebapplication.h>

class SensorController : public CWF::Controller
{
public:
    QJsonObject getInformation() const
    {
        QJsonObject information;
        information["temperatura"] = 20;
        information["umidade"]     = 10;
        //Coletar as informações da placa e preencher o JSON
        return information;
    }

    void doGet(CWF::Request &req, CWF::Response &resp) const override
    {
        resp.write(getInformation());
    }
};


int main(int argc, char *argv[])
{
    CWF::CppWebApplication server(argc, argv, "C:/Users/Mouses/Desktop/server");
    server.addController<SensorController>("/sensor");
    //http://127.0.0.1:8080/sensor
    return server.start();
}
