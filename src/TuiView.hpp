#pragma once

#include <memory>

namespace tracker::database
{
    class SqlDatabase;
}  // namespace tracker::database

namespace tracker::controller
{
    class TuiController;
}  // namespace tracker::controller

namespace tracker::view
{
class TuiView
{
public:
    TuiView(
        std::shared_ptr<controller::TuiController> controller,
        std::shared_ptr<database::SqlDatabase> model);

    void initDisplayLoop();
    void drawMenu();
    int clampedHighlightPos();

    ~TuiView();
    
private:
    std::shared_ptr<controller::TuiController> controller;
    std::shared_ptr<database::SqlDatabase> model;
    
    int highlight = 0;
    int width = 0;
    int height = 0;
    char* menuFields[4] = {
	"MENU",	
	"ADD ROW",	
	"DISPLAY DATABASE",	
	"EXIT",	
    };
};

}  // namespace tracker::view
