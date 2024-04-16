#include "core/Application.h"
#include "scenes/ExampleScene.h"
#include "scenes/Assignment1.h"
#include "scenes/Assignment2.h"
#include "scenes/Assignment3.h"

int main(int argc, char** argv) {
    // Add newly created scenes here so that they show up in the menu.
    std::vector<Scene*> scenes = {
        new Assignment3,
        new Assignment2,
        new Assignment1(),
        new ExampleScene(),
    };
    Application app(scenes);
    return app.Run();
}
