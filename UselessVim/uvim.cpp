#include <cstdio>
#include <cstdlib>
#include <curses.h>
#include <vector>

int main() 
{
  std::vector<char> buffer;
  
  buffer.insert(buffer.end(), ' ');
  
  int pos_x, pos_y;

  initscr();

  start_color();
  init_pair(1, COLOR_WHITE, COLOR_RED);

  curs_set(0);
  keypad(stdscr, 1);
  //scrollok(stdscr, true);
  noecho();
  
  getyx(stdscr, pos_y, pos_x);
  move(pos_y, pos_x);
  refresh();

  while (1) 
  {
    int lines = 0;
    int cur_line = 0;
    
    //Clears screen after every display
    clear();
    refresh();    
    
    //Display what is written on the buffer
    for (unsigned int i = 0; i < buffer.size(); i++)
    {
      //My own pesudo cursor
      if (i == unsigned(pos_x))
      {
        attron(COLOR_PAIR(1));
        printw("%c", buffer[i]);
        attroff(COLOR_PAIR(1));
      }
      else 
      {
        printw("%c", buffer[i]);
      }

      if (buffer[i] == '\n')
      {
        lines++;
      }
    }

    for (int i = 0; i < pos_x; i++)
    {
      if (buffer[i] == '\n')
      {
        cur_line++;
      }
    }

  int ch = getch();

    switch (ch) {
      case 259: //Arrow up
        for (int i = pos_x; i > 0; i--)
        {
          if (buffer[i] == '\n')
          {
            pos_x = i - 1;
            break;
          }
        }
        scrl(-1);
        ch = 0;
        break;
      case 258: //Arrow down
        for (unsigned int i = pos_x; i < buffer.size(); i++) 
        {
          if (buffer[i] == '\n')
          {
            pos_x = i + 1;
            break;
          }
        }
        scrl(1);
        ch = 0;
        break;
      case 261: //Arrow right
        if (unsigned(pos_x) < buffer.size() - 1) 
        {
          pos_x++;

          if (buffer[pos_x] == '\n')
          {
            pos_x--;
          }

        }
        ch = 0;
        break;
      case 260: //Arrow left
        //Prevents accesing negative number
        if (pos_x != 0) 
        {
          pos_x--;

          if (buffer[pos_x] == '\n')
          {
            pos_x++;
          }
        }
        ch = 0;
        break;
      case KEY_BACKSPACE:
        if (pos_x > 0) 
        {
          pos_x--;
          buffer.erase(buffer.begin() + pos_x);
        }
        ch = 0;
        break;
      default:
        pos_x++;
        break;
    }
    
    if (ch != 0)
    {
      buffer.insert(buffer.begin() + pos_x - 1, ch);
    }

    if (ch == '\n') //Gives space before 'new line' 
    {
      buffer.insert(buffer.begin() + pos_x - 1, ' ');
      pos_x++;
    }

    move(pos_y, pos_x);
    refresh();
  }
  endwin();
  
  //file.close();
  exit(0);

  return 0;
}
