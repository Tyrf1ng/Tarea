# Nombre del ejecutable
EXECUTABLE = Tarea

# Compilador
CXX = g++

# Opciones de compilación
CXXFLAGS = -std=c++11 -pthread -Wall

# Archivos fuente
SOURCES = Tarea.cpp

# Archivos objeto
OBJECTS = $(SOURCES:.cpp=.o)

# Regla principal: compila el programa
all: $(EXECUTABLE)

# Regla para compilar el ejecutable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJECTS)

# Regla para compilar archivos .cpp a .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para limpiar los archivos objeto y el ejecutable
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
