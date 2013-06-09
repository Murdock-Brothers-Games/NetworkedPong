#include "pongstate.h"
#include <QMessageBox>

PongState::PongState(int screenWidth, int screenHeight,
                     QWidget* parent):
    GameState(screenWidth, screenHeight, parent),
    _p1PaddleUp(false),
    _p1PaddleDown(false),
    _p2PaddleUp(false),
    _p2PaddleDown(false),
    _playerOneScore(0),
    _playerTwoScore(0),
    _scoreToWin(10),
    _paddleVelPerSec(0.0f),
    _ballVelPerSec(0.0f),
    _paddleStartY(0.0f),
    _paddleOneStartX(0.0f),
    _paddleTwoStartX(0.0f)
{
    //Seed the random number generator
    srand(time(NULL));
    setName(QString("Pong"));
    this->setFocusPolicy(Qt::StrongFocus);

    _paddleVelPerSec = (float)(screenHeight*1.25f);
    _ballVelPerSec = _paddleVelPerSec*.85f;
    qDebug() << "PongState::PongState(): paddleVelPerSec = " << _paddleVelPerSec;
    _playerOneScore = 0;
    _playerTwoScore = 0;
    _scoreToWin = 10;
}

PongState::~PongState()
{

}

void PongState::buildAssets()
{
    //Build the assets for the game.
    float paddleWidth = (float)(_screenWidth) / 20.0f;
    float paddleHeight = (float)(_screenHeight) / 4.0f;
    Volume paddleVol(paddleWidth, paddleHeight, 0.0f, false);
    _paddleStartY = ((float)(_screenHeight) * 0.5f) - (paddleHeight*0.5f);
    _paddleOneStartX = 0.0f;
    _paddleTwoStartX = _screenWidth-paddleWidth;

    Appearance pongAppearance;
    pongAppearance.r = 1.0f;
    pongAppearance.g = 0.0f;
    pongAppearance.b = 0.0f;
    pongAppearance.alpha = 1.0f;
    pongAppearance.textured = false;

    Appearance paddleAppearance;
    //QImage paddleTexture("C:\\Users\\Chris\\Pictures\\PongGameArt\\lightningArcCropped.png");
    //QImage paddleTexture(":/images/lightningArcCropped.png");
    QImage paddleTexture(":/images/lightningArc.png");
    if(paddleTexture.isNull()){
        qDebug() << "Error: could not load texture image.";
    }else{
        //First, ensure we make the regions of the image
        //transparent that should be.  Replace any part of
        //the texture that matches this color with transparency.
        //QRgb alphaColor = qRgb(1.0f, 0.0f, 1.0f);
        QRgb alphaColor = qRgb(0.0f, 0.0f, 0.0f);
        QImage texAlpha = paddleTexture.createMaskFromColor(alphaColor, Qt::MaskOutColor);
        const unsigned int texHeight = paddleTexture.height();
        const unsigned int texWidth = paddleTexture.width();
        for(unsigned int i = 0; i < texHeight; ++i){
            for(unsigned int j = 0; j < texWidth; ++j){
                QRgb curPixel = paddleTexture.pixel(j,i);
                QRgb alphaPixel = qRgba(qRed(curPixel), qGreen(curPixel),
                                        qBlue(curPixel),
                                        qRed(texAlpha.pixel(j,i)) );
                paddleTexture.setPixel(j, i, alphaPixel);
            }
        }
        //We have now replaced the alpha channel in "paddleTexture"
        //with the alpha channel we dictated with our newly
        //created alpha mask.
    }
    paddleAppearance.texture = paddleTexture;
    paddleAppearance.texStartX = 0.0f;
    paddleAppearance.texEndX = 1.0f;
    paddleAppearance.texStartY = 0.0f;
    paddleAppearance.texEndY = 1.0f;
    paddleAppearance.texImageWidth = paddleAppearance.texture.width();
    paddleAppearance.texImageHeight = paddleAppearance.texture.height();
    paddleAppearance.textured = true;


    //Player one starting position:
    Position p1Pos(_paddleOneStartX, _paddleStartY, 0.0f);
    BoundingBox2D p1HBox(p1Pos, paddleVol);

    _playerOne = new GameObject(QString("playerOne"), p1Pos, this);
    _playerOne->setPosition(p1Pos);
    _playerOne->setVolume(paddleVol);
    _playerOne->setHitBox(p1HBox);
    //_playerOne->setAppearance(pongAppearance);
    _playerOne->setAppearance(paddleAppearance);
    _playerOne->setCollidable(true);
    _playerOne->setSolid(true);
    _playerOne->setMobile(true);
    _playerOne->setPlayable(true);
    _playerOne->setInteractive(false);

    _playerOne->print();

    //Player two starting position:
    Position p2Pos(_paddleTwoStartX, _paddleStartY, 0.0f);
    BoundingBox2D p2HBox(p2Pos, paddleVol);

    _playerTwo = new GameObject(QString("playerTwo"), p2Pos, this);
    _playerTwo->setPosition(p2Pos);
    _playerTwo->setVolume(paddleVol);
    _playerTwo->setHitBox(p2HBox);
    //_playerTwo->setAppearance(pongAppearance);
    _playerTwo->setAppearance(paddleAppearance);
    _playerTwo->setCollidable(true);
    _playerTwo->setSolid(true);
    _playerTwo->setMobile(true);
    _playerTwo->setPlayable(true);
    _playerTwo->setInteractive(false);

    _playerTwo->print();

    //Ball
    Position ballPos((_screenWidth*0.5f),(_screenHeight*0.5f),0.0f);
    Volume ballVol(_screenWidth*0.075f, _screenHeight*0.075f, 0.0f);

    Position ballHBoxPos(ballPos.x + (ballVol.width*0.1f),
                         ballPos.y + (ballVol.height*0.1f),
                         0.0f);
    Volume ballHBoxVol(ballVol.width - (ballVol.width*0.2f),
                       ballVol.height - (ballVol.height*0.2f),
                       0.0f);
    BoundingBox2D ballHBox(ballHBoxPos, ballHBoxVol);
    Appearance ballAppearance;
   // QImage baseTexture("PongGameArt\EnergyBall.jpg");
    //QImage maskTexture = baseTexture.createMaskFromColor(QRgb(0,0,0), Qt::MaskOutColor);
    //QImage ballTexture("C:\\Users\\Chris\\Pictures\\PongGameArt\\EnergyBallCropped2.png");
    //QImage ballTexture(":/images/EnergyBallCropped2.png");
    QImage ballTexture(":/images/EnergyBall.png");
    if(ballTexture.isNull()){
        qDebug() << "Error: could not load texture image.";
    }else{
        //First, ensure we make the regions of the image
        //transparent that should be.  Replace any part of
        //the texture that matches this color with transparency.
        //QRgb alphaColor = qRgb(1.0f, 0.0f, 1.0f);
        QRgb alphaColor = qRgb(0.0f, 0.0f, 0.0f);
        QImage texAlpha = ballTexture.createMaskFromColor(alphaColor, Qt::MaskOutColor);
        const unsigned int texHeight = ballTexture.height();
        const unsigned int texWidth = ballTexture.width();
        for(unsigned int i = 0; i < texHeight; ++i){
            for(unsigned int j = 0; j < texWidth; ++j){
                QRgb curPixel = ballTexture.pixel(j,i);
                QRgb alphaPixel = qRgba(qRed(curPixel), qGreen(curPixel),
                                        qBlue(curPixel),
                                        qRed(texAlpha.pixel(j,i)) );
                ballTexture.setPixel(j, i, alphaPixel);
            }
        }
        //We have now replaced the alpha channel in "ballTexture"
        //with the alpha channel we dictated with our newly
        //created alpha mask.
    }
    //ballAppearance.texture = QImage("PongGameArt\EnergyBall.jpg");
    ballAppearance.texture = (ballTexture);
    ballAppearance.textured = true;
    ballAppearance.texStartX = 0.0f;
    ballAppearance.texEndX = 1.0f;
    ballAppearance.texStartY = 0.0f;
    ballAppearance.texEndY = 1.0f;
    ballAppearance.texImageWidth = ballAppearance.texture.width();
    ballAppearance.texImageHeight = ballAppearance.texture.height();
    _ball = new GameObject(QString("ball"), ballPos, this);
    _ball->setPosition(ballPos);
    _ball->setVolume(ballVol);
    _ball->setHitBox(ballHBox);
    //_ball->setAppearance(pongAppearance);
    _ball->setAppearance(ballAppearance);
    _ball->setCollidable(true);
    _ball->setSolid(true);
    _ball->setMobile(true);
    _ball->setPlayable(false);
    _ball->setInteractive(false);

    _ball->print();

    //Walls
    Volume wallVol(_screenWidth, _screenHeight*0.1f, 0.0f);

    Appearance wallAppearance;
    //QImage wallTexture("C:\\Users\\Chris\\Pictures\\PongGameArt\\metalTexture.png");
    QImage wallTexture(":/images/metalTexture.png");
    wallAppearance.texture = wallTexture;
    wallAppearance.texStartX = 0.0f;
    wallAppearance.texEndX = 1.0f;
    wallAppearance.texStartY = 0.0f;
    wallAppearance.texEndY = 0.5f;
    wallAppearance.texImageWidth = wallAppearance.texture.width();
    wallAppearance.texImageHeight = wallAppearance.texture.height();
    wallAppearance.textured = true;
    //Bottom Wall
    Position bWallPos(0.0f, 0.0f, 0.0f);
    BoundingBox2D bWallHBox(bWallPos, wallVol);

    _bottomWall = new GameObject(QString("bottomWall"), bWallPos, this);
    _bottomWall->setPosition(bWallPos);
    _bottomWall->setVolume(wallVol);
    _bottomWall->setHitBox(bWallHBox);
    //_bottomWall->setAppearance(pongAppearance);
    _bottomWall->setAppearance(wallAppearance);
    _bottomWall->setCollidable(true);
    _bottomWall->setSolid(true);
    _bottomWall->setMobile(true);
    _bottomWall->setPlayable(false);
    _bottomWall->setInteractive(false);

    _bottomWall->print();

    //Top Wall
    Position tWallPos(0.0f, _screenHeight-wallVol.height, 0.0f);
    BoundingBox2D tWallHBox(tWallPos, wallVol);

    _topWall = new GameObject(QString("topWall"), tWallPos, this);
    _topWall->setPosition(tWallPos);
    _topWall->setVolume(wallVol);
    _topWall->setHitBox(tWallHBox);
    //_topWall->setAppearance(pongAppearance);
    _topWall->setAppearance(wallAppearance);
    _topWall->setCollidable(true);
    _topWall->setSolid(true);
    _topWall->setMobile(true);
    _topWall->setPlayable(false);
    _topWall->setInteractive(false);

    _topWall->print();

    _screen->addGameObject(_ball);
    _screen->addGameObject(_playerOne);
    _screen->addGameObject(_playerTwo);
    _screen->addGameObject(_topWall);
    _screen->addGameObject(_bottomWall);

}

void PongState::update(float dt)
{
    //qDebug() << QString("PongState::update(): called with %1 seconds").arg(dt);
    //Move according to user input
    _ball->update(dt);
    _playerOne->update(dt);
    _playerTwo->update(dt);

    //Check collision, readjust
    checkBallWallCollision();
    checkPaddleWallCollision();
    checkBallPaddleCollision();

    //Check score
    checkGoalScored();
}

void PongState::handleInput()
{
    //qDebug() << "PongState::handleInput()";
    Velocity p1Vel = _playerOne->getVelocity();
    Velocity p2Vel = _playerTwo->getVelocity();
    if( _p1PaddleUp ){
        p1Vel.y = _paddleVelPerSec;
    }else if(_p1PaddleDown ){
        p1Vel.y = -_paddleVelPerSec;
    }else{
        p1Vel.y = 0.0f;
    }
    _playerOne->setVelocity(p1Vel);

    if( _p2PaddleUp ){
        p2Vel.y = _paddleVelPerSec;
    }else if( _p2PaddleDown ){
        p2Vel.y = -_paddleVelPerSec;
    }else{
        p2Vel.y = 0.0f;
    }
    _playerTwo->setVelocity(p2Vel);
}

void PongState::startGame()
{
    _playerOneScore = 0;
    _playerTwoScore = 0;
    Position p1Pos(_paddleOneStartX, _paddleStartY, 0.0f);
    Position p2Pos(_paddleTwoStartX, _paddleStartY, 0.0f);
    Velocity paddleVel(0.0f, 0.0f, 0.0f);
    _playerOne->setPosition(p1Pos);
    _playerOne->setVelocity(paddleVel);
    _playerTwo->setPosition(p2Pos);
    _playerTwo->setVelocity(paddleVel);
    serveBall();
}

void PongState::keyPressEvent(QKeyEvent *k) {
    switch(k->key()) {
        case Qt::Key_Up:
            _p2PaddleUp = true;
            //qDebug() << "PongState::keyPressEvent(): pressed up key!";
            break;
        case Qt::Key_Down:
            _p2PaddleDown = true;
            //qDebug() << "PongState::keyPressEvent(): pressed down key!";
            break;
        case Qt::Key_W:
            _p1PaddleUp = true;
            //qDebug() << "PongState::keyPressEvent(): pressed w key!";
            break;
        case Qt::Key_S:
            _p1PaddleDown = true;
            //qDebug() << "PongState::keyPressEvent(): pressed s key!";
            break;
        default :
            break;
    }
    k->accept();
}

void PongState::keyReleaseEvent(QKeyEvent *k) {
    switch(k->key()) {
        case Qt::Key_Up:
            _p2PaddleUp = false;
            break;
        case Qt::Key_Down:
            _p2PaddleDown = false;
            break;
        case Qt::Key_W:
            _p1PaddleUp = false;
            break;
        case Qt::Key_S:
            _p1PaddleDown = false;
            break;
        default :
            break;
    }
    k->accept();
}

void PongState::checkBallWallCollision()
{
    BoundingBox2D ball = _ball->getHitBox();
    BoundingBox2D tWall = _topWall->getHitBox();
    BoundingBox2D bWall = _bottomWall->getHitBox();

    Position ballPos = _ball->getPosition();
    Velocity ballVel = _ball->getVelocity();
    Volume ballVol = _ball->getVolume();

    if( ball.intersectsY(tWall) ){
        ballPos.y = tWall.startY - ballVol.height;
        _ball->setPosition(ballPos);
        ballVel.y *= -1.0f;
        _ball->setVelocity(ballVel);
    }
    if( ball.intersectsY(bWall) ){
        ballPos.y = bWall.endY;
        _ball->setPosition(ballPos);
        ballVel.y *= -1.0f;
        _ball->setVelocity(ballVel);
    }
}

void PongState::checkPaddleWallCollision()
{
    BoundingBox2D tWall = _topWall->getHitBox();
    BoundingBox2D bWall = _bottomWall->getHitBox();
    BoundingBox2D p1Paddle = _playerOne->getHitBox();
    BoundingBox2D p2Paddle = _playerTwo->getHitBox();

    if( p1Paddle.intersectsY(tWall) ){
        Velocity p1Vel = _playerOne->getVelocity();
        Position p1Pos = _playerOne->getPosition();
        Position tWallPos = _topWall->getPosition();
        Volume p1Vol = _playerOne->getVolume();
        p1Vel.y = 0.0f;
        p1Pos.y = (tWallPos.y - p1Vol.height);
        _playerOne->setVelocity(p1Vel);
        _playerOne->setPosition(p1Pos);
    }
    if( p2Paddle.intersectsY(tWall) ){
        Velocity p2Vel = _playerTwo->getVelocity();
        Position p2Pos = _playerTwo->getPosition();
        Position tWallPos = _topWall->getPosition();
        Volume p2Vol = _playerTwo->getVolume();
        p2Vel.y = 0.0f;
        p2Pos.y = (tWallPos.y - p2Vol.height);
        _playerTwo->setVelocity(p2Vel);
        _playerTwo->setPosition(p2Pos);
    }
    if( p1Paddle.intersectsY(bWall) ){
        Velocity p1Vel = _playerOne->getVelocity();
        Position p1Pos = _playerOne->getPosition();
        Position bWallPos = _bottomWall->getPosition();
        Volume bWallVol = _bottomWall->getVolume();
        p1Vel.y = 0.0f;
        p1Pos.y = ((bWallPos.y + bWallVol.height));
        _playerOne->setVelocity(p1Vel);
        _playerOne->setPosition(p1Pos);
    }
    if( p2Paddle.intersectsY(bWall) ){
        Velocity p2Vel = _playerTwo->getVelocity();
        Position p2Pos = _playerTwo->getPosition();
        Position bWallPos = _bottomWall->getPosition();
        Volume bWallVol = _bottomWall->getVolume();
        p2Vel.y = 0.0f;
        p2Pos.y = ((bWallPos.y + bWallVol.height));
        _playerTwo->setVelocity(p2Vel);
        _playerTwo->setPosition(p2Pos);
    }
}

void PongState::checkBallPaddleCollision()
{
    BoundingBox2D ball = _ball->getHitBox();
    BoundingBox2D p1Paddle = _playerOne->getHitBox();
    BoundingBox2D p2Paddle = _playerTwo->getHitBox();

    Position ballPos = _ball->getPosition();
    Volume ballVol = _ball->getVolume();
    Velocity ballVel = _ball->getVelocity();
    if( (ball.intersectsX(p1Paddle) && ball.intersectsY(p1Paddle)) ){
        ballVel.x *= -1.0f;
        //Speed up the ball every time it gets hit
        if( ballVel.x > 0 ){
            ballVel.x += 25.0f;
        }else{
            ballVel.x -= 25.0f;
        }
        _ball->setVelocity(ballVel);

        ballPos.x = p1Paddle.endX;
        _ball->setPosition(ballPos);
    }else if( (ball.intersectsX(p2Paddle) && ball.intersectsY(p2Paddle)) ){
        ballVel.x *= -1.0f;
        //Speed up the ball every time it gets hit
        if( ballVel.x > 0 ){
            ballVel.x += 25.0f;
        }else{
            ballVel.x -= 25.0f;
        }
        _ball->setVelocity(ballVel);

        ballPos.x = p2Paddle.startX - ballVol.width;
        _ball->setPosition(ballPos);
    }
}

void PongState::checkGoalScored()
{
    //Position ballPos = _ball->getPosition();
    BoundingBox2D ballPos = _ball->getHitBox();

    bool goalScored = false;
    if( ballPos.endX < 0.0f ){
        _playerTwoScore++;
        goalScored = true;

    }else if( ballPos.startX > _screenWidth ){
        _playerOneScore++;
        goalScored = true;
    }
    //check for win
    if( (_playerOneScore == _scoreToWin) ||
        (_playerTwoScore == _scoreToWin) ){
        int winner = (_playerOneScore == _scoreToWin ? 1 : 2);
        //Handle any score stuff
        QMessageBox::information(this, "Winner",
                                 QString("Player %1 wins!").arg(winner));
        //Instead of quitting, just reset the game.
        //User can close the game whenever they want.
        //emit gameOver();
        startGame();

    }else if(goalScored){
        serveBall();
    }
}

void PongState::serveBall()
{
    Position ballPos((_screenHeight*0.5f),(_screenHeight*0.5f),0.0f);
    _ball->setPosition(ballPos);

    //Set to a random velocity direction
    //(rand() / RAND_MAX) generates a random
    //number between 0 and 1.
    float randMult = ((float)rand() / (float)RAND_MAX);
    float coinFlipVert = ((float)rand() / (float)RAND_MAX);
    float coinFlipHoriz = ((float)rand() / (float)RAND_MAX);
    //Chooses a random x-component to the velocity but
    //guarantees that it is at least 100 pixels per second
    //in the horizontal.
    float xComp = (randMult*(_ballVelPerSec-100.0f))+100.0f;
    if( coinFlipHoriz > 0.5f ){
        xComp *= -1.0f;
    }
    //Corresponding y velocity is chosen
    //by solving for y  in the pythagorean theorum
    //(hypotenuse^2 = x^2 + y^2).  The idea is that while the direction
    //of the velocity will vary, the magnitude of the velocity
    //will always be the same, and it will always
    //be equal to _ballVelPerSec.
    float yComp = sqrt(pow(_ballVelPerSec, 2.0f) - pow(xComp, 2.0f));
    if( coinFlipVert > 0.5f ){
        yComp *= -1.0f;
    }
    Velocity ballVel(xComp, yComp, 0.0f);
    _ball->setVelocity(ballVel);

}
