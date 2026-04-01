#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution
{
public:
    /*
    struct robot
    make array of robots
    sort according to position
    loop through array
    if robot goes right add it to stack
    if robot goes left
        check who dies
            if right dies
                remove it from the stack and keep the left robot and decrease its health by one and compare it again with the stack top
            check if stack is empty
                put the left into res
            else if left dies
                decrease the health of the right robot and put it back into the stack
            else (both dies)
                remove the right robot from the stack and continue to the next robot in the loop

    if stack not empty
        put all robots in it in res
    sort res according to index

    return res;


    */

    struct Robot
    {
        int index;
        int pos;
        int health;
        char dir;
    };
    vector<Robot> robots;
    vector<Robot> resRob;
    vector<int> survivedRobotsHealths(vector<int> &positions, vector<int> &healths, string directions)
    {
        for (int i = 0; i < positions.size(); i++)
        {
            Robot robot = {i, positions[i], healths[i], directions[i]};
            robots.push_back(robot);
        }
        sort(robots.begin(), robots.end(), [](const Robot &r1, const Robot &r2)
             { return r1.pos < r2.pos; });
        stack<Robot> st;
        for (int i = 0; i < robots.size();)
        {
            Robot *r = &robots[i];
            if (r->dir == 'R')
            {
                st.push(*r);
                i++;
                continue;
            }
            if (st.empty())
            {
                resRob.emplace_back(*r);
                i++;
            }
            else
            {
                Robot *topRobot = &st.top();
                // right dies
                if (topRobot->health < r->health)
                {
                    st.pop();
                    r->health--;
                }
                // left dies
                else if (topRobot->health > r->health)
                {
                    st.top().health--;
                    i++;
                }
                // both dies
                else
                {
                    st.pop();
                    i++;
                }
            }
        }
        while (!st.empty())
        {
            resRob.emplace_back(st.top());
            st.pop();
        }

        sort(resRob.begin(), resRob.end(), [](const Robot &r1, const Robot &r2)
             { return r1.index < r2.index; });
        vector<int> res;
        for (const Robot r : resRob)
        {
            res.emplace_back(r.health);
        }
        return res;
    }
};