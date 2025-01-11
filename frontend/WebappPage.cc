// Jakub Rozkosz

#include <Wt/WMessageBox.h>
#include "WebappPage.h"

using namespace std;

WebappPage::WebappPage(const Wt::WEnvironment& env) : Wt::WApplication(env) {}

void WebappPage::showMessageDialog(const string& type, const string& message) {
    messageBox_ = make_unique<Wt::WMessageBox>(
        type,
        message,
        Wt::Icon::Information, Wt::StandardButton::Ok);

    messageBox_->setStyleClass("custom-message-box");
    messageBox_->contents()->setStyleClass("custom-message-box-contents");
    messageBox_->titleBar()->setStyleClass("custom-message-box-title");
    messageBox_->footer()->setStyleClass("custom-message-box-footer");

    messageBox_->buttonClicked().connect([this] {
        messageBox_->accept();
    });

    messageBox_->show();
}

unique_ptr<Wt::WMessageBox>& WebappPage::getMessageBoxText() {
    return messageBox_;
}