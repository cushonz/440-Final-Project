class Game {

    public:

        Game(int diff,float score = 0);
        bool takeDamage();
        bool isDead();
        void gainPoint(float amount);

    private:
        int remaining_lives=3;
        int remaining_hearts;
        float score;
        int multiplier = 1;

};