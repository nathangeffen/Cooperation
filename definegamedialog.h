#ifndef DEFINEGAMEDIALOGUE_H
#define DEFINEGAMEDIALOGUE_H

#include <map>
#include <vector>

#include <QtGui>

using namespace std;

class ColorPickButton : public QPushButton
{
public:
  ColorPickButton( int i, QWidget *parent ) :
    QPushButton(parent), index_(i) { setText( tr("Choose color") ); }
  int getIndex() const { return index_; }
private:
  int index_;
};


class DefineGameDialog : public QDialog
{
  Q_OBJECT

public:
  DefineGameDialog(QWidget* parent = 0);
  void setIterations(int i) { iterationsEdit_->setValue(i); }
  void setRandomSeed( int i ) { randomSeedEdit_->setValue(i); }
  void setUpdateFrequency(int i) { updateFrequencyEdit_->setValue(i); }
  void setUpdateStyle(int i) { updateStyleCombo_->setCurrentIndex(i); }
  void setCompetitors( const map<QString, int> nCompetitorsMap );
  void setCompetitorColors( const map<QString, QColor>& colors );
  void setTimer(int i) { timerEdit_->setValue(i); }
  void setNumberForAllCompetitors( int i );

  int getIterations() const { return iterationsEdit_->text().toInt(); }
  int getRandomSeed() const { return randomSeedEdit_->text().toInt(); }
  int getUpdateFrequency() const { return updateFrequencyEdit_->text().toInt(); }
  int getUpdateStyle() const { return updateStyleCombo_->currentIndex(); }
  int getTimer() const { return timerEdit_->text().toInt(); }
  vector<int> getCompetitors() const;
  map<QString, QColor> getCompetitorColors() const;

signals:
  void specificButtonClicked( int );

private slots:
  void colorButtonClicked();
  void runColorDialog( int );
  void setLineEditColor( QString );

private:
  void setLineEditColor( QLineEdit* edit );
  QSpinBox* nCompetitorsSpinBox( int i );

  QGridLayout* layout_;
  QGridLayout* competitorLayout_;
  QHBoxLayout* buttonLayout_;

  QPushButton* apply_;
  QPushButton* cancel_;
  QLabel* iterationsLabel_;
  QSpinBox* iterationsEdit_;

  QLabel* randomSeedLabel_;
  QSpinBox* randomSeedEdit_;

  QLabel* updateFrequencyLabel_;
  QSpinBox* updateFrequencyEdit_;

  QLabel* updateStyleLabel_;
  QComboBox* updateStyleCombo_;

  QLabel* timerLabel_;
  QSpinBox* timerEdit_;

  vector <QLabel*> competitorLabels_;
  vector <QSpinBox*> competitorNumbers_;
  vector <QLineEdit*> competitorColors_;
  vector <ColorPickButton*> colorButtons_;
};

#endif // DEFINEGAMEDIALOGUE_H
