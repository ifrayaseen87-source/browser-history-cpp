#include <iostream>
using namespace std;

class Page {
public:
    int count;
    string URL, title, timestamp, userID;
    Page* next;
    Page* prev;

    Page(int c, string url, string t, string time, string user) {
        count = c;
        URL = url;
        title = t;
        timestamp = time;
        userID = user;
        next = NULL;
        prev = NULL;
    }
};

class BrowserHistory {
public:
    Page* head;
    Page* tail;
    int size;

    BrowserHistory() {
        head = NULL;
        tail = NULL;
        size = 0;
    }

    // Add new page
    void addPage(int c, string url, string t, string time, string user) {
        Page* newPage = new Page(c, url, t, time, user);

        if (head == NULL) {
            head = tail = newPage;
        } else {
            tail->next = newPage;
            newPage->prev = tail;
            tail = newPage;
        }

        size++;
    }

    // Display full history (forward)
    void display() {
        if (head == NULL) {
            cout << "History is empty.\n";
            return;
        }

        cout << "\n--- BROWSER HISTORY ---\n";
        Page* temp = head;

        while (temp != NULL) {
            cout << "Visit " << temp->count << ": "
                 << temp->URL << " - "
                 << temp->title << " - "
                 << temp->timestamp << " - "
                 << temp->userID << endl;

            temp = temp->next;
        }

        cout << "----------------------\n";
    }

    // Move backward (just show reverse traversal)
    void backPage() {
        if (tail == NULL) {
            cout << "No page is open.\n";
            return;
        }

        cout << "\n--- BACKWARD HISTORY ---\n";
        Page* temp = tail;

        while (temp != NULL) {
            cout << temp->URL << " <- ";
            temp = temp->prev;
        }

        cout << "START\n";
    }

    // Move forward (just show forward traversal)
    void nextPage() {
        if (head == NULL) {
            cout << "No page is open.\n";
            return;
        }

        cout << "\n--- FORWARD HISTORY ---\n";
        Page* temp = head;

        while (temp != NULL) {
            cout << temp->URL << " -> ";
            temp = temp->next;
        }

        cout << "END\n";
    }

    // Delete last page
    void deletePage() {
        if (head == NULL) {
            cout << "No page exists.\n";
            return;
        }

        if (head == tail) {
            delete head;
            head = tail = NULL;
        } else {
            Page* temp = tail;
            tail = tail->prev;
            tail->next = NULL;
            delete temp;
        }

        size--;
        cout << "Last page deleted.\n";
    }

    // Search page
    Page* searchPage(string url) {
        if (head == NULL) {
            cout << "History is empty.\n";
            return NULL;
        }

        Page* temp = head;

        while (temp != NULL) {
            if (temp->URL == url) {
                cout << "Page Found: " << temp->title
                     << " (" << temp->URL << ")\n";
                return temp;
            }
            temp = temp->next;
        }

        cout << "Page NOT found!\n";
        return NULL;
    }
};

int main() {
    BrowserHistory h;

    h.addPage(1, "google.com", "Google", "10:00 AM", "Ifra Yaseen");
    h.addPage(2, "youtube.com", "YouTube", "10:05 AM", "Eman Yaseen");
    h.addPage(3, "github.com", "GitHub", "10:10 AM", "Sarim Sarmad");

    h.display();

    h.nextPage();
    h.backPage();

    h.deletePage();
    h.display();

    h.searchPage("youtube.com");

    return 0;
}
