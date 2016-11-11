class camera{

 public:
  camera::camera(){
    m_x = 0;
    m_y = 0;
    m_z = 0;
  }

  void setCamera(int x = 0, int y = 0 , int z = 0)
  {
    m_x = x;
    m_y = y;
    m_z = z;
  }

  void mooveLeft(){
    m_x = m_x - 1;
  }
  void mooveRight(){
    m_x = m_x + 1;
  }
  void mooveUp(){
    m_y = m_y + 1;
  }
  void mooveDown(){
    m_y = m_y - 1;
  }

 private:
  int m_x;
  int m_y;
  int m_z;
}
