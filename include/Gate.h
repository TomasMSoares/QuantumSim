#include <vector>
#include <string>

enum class GateType {
    PauliX,
    PauliY,
    PauliZ,
    Hadamard,
    Custom
};

class Gate {
public:
    Gate(GateType type) : _type(type) {};

private:
    GateType _type;

    /*
    This attribute should only be initialized in the case of a custom matrix
    */
    std::vector<std::vector<double>> matrix;
};