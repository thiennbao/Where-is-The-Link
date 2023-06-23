void mask(char str[], char mask = char(255)) {
    int i = 0;
    while (str[i] != '\0') {
        str[i] ^= mask;
        i++;
    }
}

void drawLogo() {
    GoTo(0, 2);
    ifstream ifs("assets/logo.dat", ios::binary);
    if (ifs.is_open()) {
        char str[121];
        while (!ifs.eof()) {
            ifs.read(str, 121);
            if (ifs.eof()) {
                return;
            }
            mask(str);
            cout << str << endl;
        }
    }
}
