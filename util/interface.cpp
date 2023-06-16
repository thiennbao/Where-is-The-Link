
void drawLogo() {
    ifstream ifs("assets/logo.txt");
    if (ifs.is_open()) {
        string str;
        int y = 1;
        while (!ifs.eof()) {
            getline(ifs, str);
            GoTo(windowWidth/2 - str.length()/2, ++y);
            cout << str << endl;
        }
    }
}
