#include "Application.hpp"


void Application::processEvent(sf::Clock deltaClock)
{
    sf::Event event;

    static sf::Clock    clickDelta;
    static sf::Vector2i clickPos;
           bool         isDoubleClick{false};

    while (m_window.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);

        switch(event.type){
            case(sf::Event::Closed):
                m_window.close();
                break;

            case(sf::Event::MouseMoved):
                m_mouseInActiveZone = 
                event.mouseMove.x < (m_window.getSize().x - m_uiWidth)? true :
                                                                        false;
                break;

            case(sf::Event::MouseWheelMoved):
                if(m_mouseInActiveZone)
                {
                    m_figure->relScale((event.mouseWheel.delta)*ZOOM_SPEED);

                    if(m_figure->scale() > MAX_SCALE) m_figure->scale(MAX_SCALE);
                    if(m_figure->scale() < MIN_SCALE) m_figure->scale(MIN_SCALE);

                    m_figure->update();
                    break;
                }

            case(sf::Event::MouseButtonPressed):
                if(event.mouseButton.button == sf::Mouse::Button::Left
                   && m_mouseInActiveZone)
                {
                    if(clickDelta.restart().asSeconds() < DOUBLE_CLICK_GAP)
                    {
                        isDoubleClick = true;
                    }
                    clickPos = sf::Mouse::getPosition(m_window);
                    m_figureIsGrabbed = true;
                    break;
                }

            case(sf::Event::MouseButtonReleased):
                if(event.mouseButton.button == sf::Mouse::Button::Left)
                {
                    m_point = m_figure->center();
                    m_figureIsGrabbed = false;
                    break;
                }
        }
    }

    if (isDoubleClick && m_mouseInActiveZone)
    {
        m_point = m_canvasCenter;
        m_figure->center(m_canvasCenter);
        m_figure->update();
    }


    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)
        && m_window.hasFocus()
        && clickDelta.getElapsedTime().asSeconds() > MOVING_DELAY
        && m_figureIsGrabbed)
    {
        auto offset = sf::Mouse::getPosition(m_window) - clickPos;
        m_figure->center(m_point + sf::Vector2f(offset));
        m_figure->update();
    }

    ImGui::SFML::Update(m_window, deltaClock.restart());
}

void Application::render()
{
    m_bg.draw(m_renderTexture[0]);
    m_figure->draw(m_renderTexture[1]);

    m_window.clear();

    for(auto sprite: m_sprite){
        m_window.draw(sprite);
    }

    m_window.resetGLStates();

    UI();

    m_window.display();
}


void Application::run()
{
    sf::Clock deltaClock;
    while (m_window.isOpen())
    {
        processEvent(deltaClock);
        render();
    }

    ImGui::SFML::Shutdown();
}

void Application::UI()
{
    struct Item
    {
        const char*        label;
        int                current_item;
        std::vector<char*> items;

        Item(char* _label, std::vector<char*> _items, int _current_item = 0):
                label(_label), items(_items), current_item(_current_item){}
    };

    static Item type ("##Type",
                      std::vector<char*> {"Gasket", "Curve"});

    static std::vector<Item> subType{
        Item("##Gasket_Subtype", std::vector<char*> {"Sierpinski sieves",
                                                     "Sierpinski carpet"}),
        Item("##Curve_Subtype",  std::vector<char*> {"Koch", "Hilbert"})
    };

    static Item koch_base ("##Koch_base",
                           std::vector<char*> {"Line", "Triangle", "Square"});

    static int   depth{m_figure->depth()};
    static float scale{m_figure->scale()};

    static int lineWidth(1);

    static int color[4]  {m_figure->color().r, m_figure->color().g,
                          m_figure->color().b, m_figure->color().a};
    static int bgColor[4]{m_bg.color().r, m_bg.color().g,
                          m_bg.color().b, m_bg.color().a};

    static bool widthIsZoomable{false};

    // Config UI
    ImGui::SetNextWindowPos(ImVec2(600,0));
    ImGui::SetNextWindowSize(ImVec2(m_uiWidth,600));

    ImGui::Begin("##Settings", NULL,  ImGuiWindowFlags_NoTitleBar|
                                      ImGuiWindowFlags_NoResize|
                                      ImGuiWindowFlags_NoMove|
                                      ImGuiWindowFlags_NoCollapse|
                                      ImGuiWindowFlags_ShowBorders);

    ImGui::Text("");

    ImGui::Text("Type");
    if(ImGui::Combo(type.label, &type.current_item,
                 type.items.data(), type.items.size())){
        switch(type.current_item){
            case(0):
                m_figure.reset(new SierpinskiTriangle);
                break;
            case(1):
                m_figure.reset(new Curve_Koch);
                break;
        }
        m_figure->create(m_point);
        m_figure->depth(depth);
        m_figure->color(sf::Color(color[0],color[1],color[2],color[3]));

        m_figure->scale(scale);
        m_figure->calculate();
    }

    ImGui::Text("");

    ImGui::Text("Subtype");
    if(ImGui::Combo( subType[type.current_item].label,
                    &subType[type.current_item].current_item,
                     subType[type.current_item].items.data(),
                     subType[type.current_item].items.size())){
        switch(type.current_item){
            case(0):
                switch(subType[type.current_item].current_item){
                    case(0):
                        m_figure.reset(new SierpinskiTriangle);
                        break;
                    case(1):
                        m_figure.reset(new SierpinskiCarpet);
                        break;
                }
                break;
            case(1):
                switch(subType[type.current_item].current_item){
                    case(0):
                        m_figure.reset(new Curve_Koch);
                        break;
                    case(1):
                        m_figure.reset(new Curve_Hilbert);
                        break;
                }
                break;
        }
        m_figure->create(m_point);
        m_figure->depth(depth);
        m_figure->color(sf::Color(color[0],color[1],color[2],color[3]));

        if(type.current_item == 1){
            Curve* curvePtr = dynamic_cast<Curve*>(m_figure.get());
            curvePtr->width(lineWidth);
            curvePtr->widthIsZoomable(widthIsZoomable);
        }

        m_figure->scale(scale);
        m_figure->calculate();
    }

    ImGui::Text("");

    if(type.current_item == 1 && subType[1].current_item == 0){
        ImGui::Text("Base");
        if(ImGui::Combo( koch_base.label,
                     &koch_base.current_item,
                      koch_base.items.data(),
                      koch_base.items.size())){
            Curve_Koch* ckPtr = dynamic_cast<Curve_Koch*>(m_figure.get());
            switch(koch_base.current_item){
                case 0:
                    ckPtr->base(Curve_Koch::Base::LINE);
                    ckPtr->needRedraw();
                    break;
                case 1:
                    ckPtr->base(Curve_Koch::Base::TRIANGLE);
                    ckPtr->needRedraw();
                    break;
                case 2:
                    ckPtr->base(Curve_Koch::Base::SQUARE);
                    ckPtr->needRedraw();
                    break;
            }

        }
    }

    ImGui::Text("");
    ImGui::Separator();
    ImGui::Text("");


    ImGui::Text("Recursion depth");
    if(ImGui::SliderInt("##Recursion depth", &depth, 0, 6)){
        m_figure->depth(depth);
        m_figure->needRedraw();
    }

    ImGui::Text("");

    ImGui::Text("Image Scale");
    if(ImGui::SliderFloat("##Image Scale", &scale, 0.5, 2)){
        m_figure->scale(scale);
        m_figure->update();
    }

    ImGui::Text("");
    ImGui::Separator();
    ImGui::Text("");

    if(type.current_item == 1){
        Curve* curvePtr = dynamic_cast<Curve*>(m_figure.get());

        ImGui::Text("Line width");
        if(ImGui::DragInt("##Line width", &lineWidth, 1, 1, 10)){
            curvePtr->width(lineWidth);
            curvePtr->needRedraw();
        }

        if(ImGui::Checkbox("is zoomable", &widthIsZoomable)){
            curvePtr->widthIsZoomable(widthIsZoomable);
            curvePtr->calcLineWidth();
            curvePtr->needRedraw();
        }


        ImGui::Text("");

        static int angle{60};
        if(type.current_item == 1){
            if(subType[1].current_item == 0){
                ImGui::Text("Angle");
                if(ImGui::DragInt("##Angle", &angle, 1, 0, 180)){
                    Curve_Koch* curvePtr = dynamic_cast<Curve_Koch*>(m_figure.get());
                    curvePtr->angle(angle);
                    curvePtr->needRedraw();
                }
            }
        }

        ImGui::Text("");
        ImGui::Separator();
        ImGui::Text("");
    }


    ImGui::Text("Fill Color");
    if(ImGui::DragInt4("##Fill Color", color, 1, 0, 255)){
        m_figure->color(sf::Color(color[0],color[1],color[2],color[3]));
        m_figure->needRedraw();
    }


    ImGui::Text("");
    ImGui::Separator();
    ImGui::Text("");


    ImGui::Text("Background color");
    if(ImGui::DragInt4("##Background color", bgColor, 1, 0, 255)){
        m_bg.color(sf::Color(bgColor[0],bgColor[1], bgColor[2],bgColor[3]));
        m_bg.needRedraw();
    }
    ImGui::End();

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowPadding.x = 32;

    // Render UI
    ImGui::Render();
}
