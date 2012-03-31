#ifndef DEFINEGAMEDIALOGUE_H
#define DEFINEGAMEDIALOGUE_H
#include <map>
#include <vector>

#include <QtGui>

using namespace std;

/**
  * Small pushbutton class that brings up Qt color select dialog
  */

class ColorPickButton : public QPushButton
{
public:
  ColorPickButton( int i, QWidget *parent ) :
    QPushButton(parent), index_(i) { setText( tr("Choose color") ); }
  int getIndex() const { return index_; }
private:
  int index_;
};


/** This class handles the main dialog in the GUI, that is used to set the
  * parameters of a new game.
  */

class DefineGameDialog : public QDialog
{
  Q_OBJECT

public:
  DefineGameDialog(QWidget* parent = 0);

  /** Sets the number of iterations for the game.
    */
  void setIterations(int i) { iterationsEdit_->setValue(i); }

  /** Sets the random seed for the game.
    */
  void setRandomSeed( int i ) { randomSeedEdit_->setValue(i); }

  /** Specify how frequently the competitor widgets are updated.
    *
    * Set the parameter to 1 for an update after every iteration.
    */
  void setUpdateFrequency(int i) { updateFrequencyEdit_->setValue(i); }

  /** Choose an update methodology that corresponds to an entry in the
    * in the DisplayMethodology.
    */
  void setUpdateStyle(int i) { updateStyleCombo_->setCurrentIndex(i); }

  /** Tells the dialog how many of each competitor there are when it starts up.
    *
    * @param[in] nCompetitorsMap a map from QString to int where the key is
    *            the name of a competitor in the registeredCompetitors global
    *            variable and the integer is the number of competitors.
    */
  void setCompetitors( const map<QString, int> nCompetitorsMap );

  /** Tells the dialog what color to initiate each competitor type to.
    *
    * @param[in] colors a map from QString to QColor where the key is
    *            the name of a competitor in the registeredCompetitors global
    *            variable and the integer is the number of competitors.
    */
  void setCompetitorColors( const map<QString, QColor>& colors );

  /** Sets the dialog's initial time in milliseconds between each iteration of
    * the game.
    */
  void setTimer(int i) { timerEdit_->setValue(i); }

  /** Convenience function to set the dialog's initial number of competitors
    * for each competitor to the same number.
    */
  void setNumberForAllCompetitors( int i );

  /** Returns the number of iterations set on the dialog by the user.
    */
  int getIterations() const { return iterationsEdit_->text().toInt(); }

  /** Returns the random seed set on the dialog by the user.
    */
  int getRandomSeed() const { return randomSeedEdit_->text().toInt(); }

  /** Returns the frequency with which the competitor widgets must be updated,
    * as set on the dialog by the user.
    */
  int getUpdateFrequency() const { return updateFrequencyEdit_->text().toInt(); }

  /** Returns the update style specified by the user on the dialog.
    */
  int getUpdateStyle() const { return updateStyleCombo_->currentIndex(); }

  /** Returns the time between iterations specified by the user on the
    * dialog.
    */
  int getTimer() const { return timerEdit_->text().toInt(); }

  /** Returns a vector of integers with each integer representing the number of
    * competitors for a particular competitor type in the global variable
    * registeredCompetitors.
    */
  vector<int> getCompetitors() const;

  /** Returns a map from QString to QColor of competitor type names and their
    * corresponding color as specified by the user on the dialog..
    */
  map<QString, QColor> getCompetitorColors() const;

signals:

  /** This signal is generated when a user clicks one of the choose color
    * pushbuttons.
    *
    * Its parameter corresponds to the index of the pushbutton.
    */
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
