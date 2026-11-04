using namespace std;

bool isLetter(char c) {
    return (c >= 'a' && c <= 'z');
}

string removeLink(const string& text) {
    string result = text;
    size_t startPos = 0;

    // Remove opening <a> tags
    while ((startPos = result.find("<a", startPos)) != string::npos) {
        size_t endPos = result.find(">", startPos);
        if (endPos != string::npos) {
            result.erase(startPos, endPos - startPos + 1); // Remove <a...>
        } else {
            break; // No closing tag found
        }
    }

    // Remove closing </a> tags
    startPos = 0;
    while ((startPos = result.find("</a>", startPos)) != string::npos) {
        result.erase(startPos, 4); // Remove </a>
    }

    return result;
}

string removeSpan(const string& texts) {
    string result = texts;
    size_t startPos = 0;

    // Remove opening <a> tags
    while ((startPos = result.find("<span", startPos)) != string::npos) {
        size_t endPos = result.find(">", startPos);
        if (endPos != string::npos) {
            result.erase(startPos, endPos - startPos + 1); // Remove <a...>
        } else {
            break; // No closing tag found
        }
    }

    // Remove closing </a> tags
    startPos = 0;
    while ((startPos = result.find("</span>", startPos)) != string::npos) {
        result.erase(startPos, 7);
    }

    return result;
}

string removeImage(const string& texts) {
    string result = texts;
    size_t startPos = 0;

    while ((startPos = result.find("<img", startPos)) != string::npos) {
        size_t endPos = result.find(">", startPos);
        if (endPos != string::npos) {
            result.erase(startPos, endPos - startPos + 1); 
        } else {
            break; 
        }
    }

    startPos = 0;
    while ((startPos = result.find("</div>", startPos)) != string::npos) {
        result.erase(startPos, 5);
    }

    return result;
}

string removeDiv(const string& texts) {
    string result = texts;
    size_t startPos = 0;

    while ((startPos = result.find("<div", startPos)) != string::npos) {
        size_t endPos = result.find(">", startPos);
        if (endPos != string::npos) {
            result.erase(startPos, endPos - startPos + 1); 
        } else {
            break; 
        }
    }

    startPos = 0;

    return result;
}

// Helper function to trim whitespace from both ends of a string
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \n\r\t");
    if (first == string::npos) return ""; // No content
    size_t last = str.find_last_not_of(" \n\r\t");
    return str.substr(first, (last - first + 1));
}

// Generic function to extract content between specified tags
vector<string> extractContents(const string& html, const string& startTag, const string& endTag, int option) {
    vector<string> contents;
    size_t startPos = 0;

    while ((startPos = html.find(startTag, startPos)) != string::npos) {
        size_t endPos = html.find(endTag, startPos);
        if (endPos == string::npos) {
            break; // No closing tag found
        }

        // Extract the content between the tags
        size_t textStart = startPos + startTag.length();
        string text = html.substr(textStart, endPos - textStart);

        if (option == 1) {
            text = startTag + text + endTag; // Recreate the full tag with content
        } else if (option == 3) {
            text = removeLink(text);
            text = removeSpan(text);
            text = removeImage(text);
            text = removeDiv(text);
        } 

        // Trim whitespace
        text = trim(text);

        if (!text.empty()) { // Option 2 is handled above
            contents.push_back(text); // Add extracted text to the vector
        }

        // Move to the next position after the current end tag
        startPos = endPos + endTag.length();
    }

    return contents;
}

// Function to extract usernames
vector<string> getUserNames(const vector<string>& contents) {
    vector<string> usernames;
    string startTag = "<span class=\"x193iq5w xeuugli x13faqbe x1vvkbs x1xmvt09 x1lliihq x1s928wv xhkezso x1gmr53x x1cpjm7i x1fgarty x1943h6x x4zkp8e x676frb x1nxh6w3 x1sibtaa x1s688f xzsf02u\" dir=\"auto\">";
    string endTag = "</span>";

    // Concatenate all lines into a single string
    string contentsStr;
    for (const auto& line : contents) {
        contentsStr += line + "\n"; // Add newline to preserve line breaks
    }

    return extractContents(contentsStr, startTag, endTag, 2);
}

// vector<string> scrapContents(const string& html) {
//     vector<string> texts;
//     string startTag = "<div class=\"xwib8y2 xn6708d x1ye3gou x1y1aw1k\">";
//     string endTag = "</div>";
    
//     size_t startPos = 0;

//     // Find all occurrences of the div tags
//     while ((startPos = html.find(startTag, startPos)) != string::npos) {
//         size_t endPos = html.find(endTag, startPos);
//         if (endPos == string::npos) {
//             break; // No closing tag found
//         }

//         // Extract the content between the tags
//         size_t textStart = startPos + startTag.length(); // Move past the closing '>'
//         string text = html.substr(textStart, endPos - textStart);
        
//         text = removeLink(text);
//         text = removeSpan(text);
//         text = removeImage(text);
//         text = removeDiv(text);
//         // text = removeSpan(text);
        
//         // Trim whitespace (if necessary)
//         text.erase(0, text.find_first_not_of(" \n\r\t")); // Left trim
//         text.erase(text.find_last_not_of(" \n\r\t") + 1); // Right trim

//         texts.push_back(text); // Add extracted text to the vector

//         // Move to the next position after the current end tag
//         startPos = endPos + endTag.length();
//     }

//     return texts;
// }

// Function to extract comments
vector<string> getComments(const vector<string>& contents) {
    string startTag = "<div dir=\"auto\" style=\"text-align: start;\">";
    string endTag = "</div>";

    // Concatenate all lines into a single string
    string contentsStr;
    for (const auto& line : contents) {
        contentsStr += line + "\n"; // Add newline to preserve line breaks
    }

    // cout<<contentsStr<<endl;

    // ofstream file("content.csv");
    // if (file.is_open()) {
    //     file << contentsStr; // Write data to file
    //     file.close(); // Close the file
    //     cout << "Data saved to Data.csv" << endl;
    // } else {
    //     cout << "Unable to open file." << endl;
    // }

    return extractContents(contentsStr, startTag, endTag, 3);
}

// Function to extract specific content from HTML
vector<string> scrapContents(const string& html) {
    string startTag = "<div class=\"xwib8y2 xn6708d x1ye3gou x1y1aw1k\">";
    string endTag = "</div>";

    return extractContents(html, startTag, endTag, 1);
}

string getUserInput(){
    string texts;
    int n = 0;
    // cout << "(Enter to return)\n1.Enter input from console\n2.Get input from file\nYour choice: ";
    // getline(cin, choice);
    cout<<"Input number of file: ";
    cin>>n;
    for(int i = 0; i < n; i++){
        string filePath = "input" + to_string(i) + ".txt";
        ifstream inputFile(filePath);
        if (!inputFile) {
            cout << "Failed to open the input file." << endl;
            continue;
        }
        // Read the entire contents of the file into 'texts'
         // Read the file content and append it to 'texts'
        stringstream buffer;
        buffer << inputFile.rdbuf(); // Read the entire file into the stringstream
        texts.append(buffer.str());
        inputFile.close();
    }
    return texts;
}

void save(/*const vector<string>& names,*/ const vector<string>& comments) {
    string data = "Comments\n";
    
    // Ensure that names and comments have the same size
    // size_t count = min(names.size(), comments.size());

    // size_t count = comments.size();

    // cout<<names.size()<<endl;
    // cout<<comments.size()<<endl;

    
    // Append each name and corresponding comment to the data
    for (const auto& comment : comments) {
            // Check if the comment contains a comma
            if (comment.find(',') == string::npos) {
                data += comment + "\n"; // Append comment with a newline
            } else {
                // Optionally handle comments with commas
                // For example, you could wrap them in quotes
                data += "\"" + comment + "\"\n";
            }
        }
    
    ofstream file("Data.csv");
    if (file.is_open()) {
        file << data; // Write data to file
        file.close(); // Close the file
        cout << "Data saved to Data.csv" << endl;
    } else {
        cout << "Unable to open file." << endl;
    }
}