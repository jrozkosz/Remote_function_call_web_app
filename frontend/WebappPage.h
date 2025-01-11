// Jakub Rozkosz

#ifndef WEBAPPPAGE_H
#define WEBAPPPAGE_H

#include <Wt/WMessageBox.h>
#include <Wt/WApplication.h>

class WebappPage : public Wt::WApplication {
private:
    std::unique_ptr<Wt::WMessageBox> messageBox_;
public:
    WebappPage(const Wt::WEnvironment& env);
    void showMessageDialog(const std::string& type, const std::string& message);
    virtual void displayContent() = 0;
    std::unique_ptr<Wt::WMessageBox>& getMessageBoxText();
};

#endif