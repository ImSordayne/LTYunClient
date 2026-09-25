#include <iostream>
#include <webview/webview.h>

int main() {
    webview::webview window(true, nullptr);
    window.set_title("蓝天新世界");
    window.set_html("<h1>Loading...</h1>");
    window.navigate("https://hiltyun.com/");
    window.run();
    return 0;
}
