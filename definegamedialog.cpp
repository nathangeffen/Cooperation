/* This source file is part of Cooperation, an implementation of the 
 * Prisoner's Dilemna game.
 *
 * Copyright (C) 2012 by Nathan Geffen 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QtGui>
#include "definegamedialog.h"
#include "game/competitor.h"

DefineGameDialog::DefineGameDialog(QWidget* parent)
  : QDialog(parent)
{
  setWindowTitle( tr("Define Game Dialog") );
  resize( 700, 300 );

  int i = 0;

  layout_ = new QGridLayout( this );

  iterationsLabel_ = new QLabel( tr("Iterations"), this );
  iterationsEdit_ = new QSpinBox( this );
  iterationsEdit_->setRange(1, 999999999);
  iterationsEdit_->setSingleStep(100);
  iterationsEdit_->setValue(1000);
  iterationsLabel_->setBuddy(iterationsEdit_);

  layout_->addWidget( iterationsLabel_, i, 0 );
  layout_->addWidget( iterationsEdit_, i, 1 );
  ++i;

  randomSeedLabel_ = new QLabel( tr("Random seed"), this);
  randomSeedEdit_ = new QSpinBox( this );
  randomSeedEdit_->setRange( 1, 999999999);
  randomSeedEdit_->setSingleStep(1);
  randomSeedEdit_->setValue( 1000 );
  randomSeedLabel_->setBuddy( randomSeedEdit_ );

  layout_->addWidget( randomSeedLabel_, i, 0 );
  layout_->addWidget( randomSeedEdit_, i, 1 );
  ++i;

  updateStyleLabel_ = new QLabel( tr("Update style"), this );
  updateStyleCombo_ = new QComboBox( this );
  updateStyleCombo_->addItem(tr("ratio"));
  updateStyleCombo_->addItem(tr("ratio with lowest set to 0"));
  updateStyleCombo_->addItem(tr("rank"));
  updateStyleLabel_->setBuddy(updateStyleCombo_);

  layout_->addWidget( updateStyleLabel_, i, 0 );
  layout_->addWidget( updateStyleCombo_, i, 1 );
  ++i;

  updateFrequencyLabel_ = new QLabel( tr("Update frequency"), this );
  updateFrequencyEdit_ = new QSpinBox( this );
  updateFrequencyEdit_->setRange(1, 999999999);
  updateFrequencyEdit_->setSingleStep(10);
  updateFrequencyEdit_->setValue(1);
  updateFrequencyLabel_->setBuddy(updateStyleCombo_);

  layout_->addWidget( updateFrequencyLabel_, i, 0 );
  layout_->addWidget( updateFrequencyEdit_, i, 1 );
  ++i;

  timerLabel_ = new QLabel( tr( "Time between updates (milliseconds)" ), this );
  timerEdit_ =  new QSpinBox( this );
  timerEdit_->setRange( 0, 100000 );
  timerEdit_->setSingleStep( 100 );
  timerEdit_->setValue( 0 );
  timerLabel_->setBuddy( timerEdit_ );

  layout_->addWidget( timerLabel_, i, 0 );
  layout_->addWidget( timerEdit_, i, 1 );
  ++i;

  /*** NOT SURE IF THIS CODE IS PRECISE ***/
  /* If "this" is passed to QGridLayout then
   * the programme stil executes ok, but it generates a message
   * "Attempting to add QLayout". If "this" is removed the message disappers
   * but this begs the question, is this object ever freed from the heap?
   */
  competitorLayout_ = new QGridLayout();

  layout_->addLayout( competitorLayout_, i, 0, 1, 4 );
  ++i;

  apply_ = new QPushButton( tr("&Ok"), this );
  connect(apply_, SIGNAL(clicked()), this, SLOT(accept()));
  cancel_ = new QPushButton(tr("&Cancel"), this );
  connect(cancel_, SIGNAL(clicked()), this, SLOT(reject()));

  /*** NOT SURE IF THIS CODE IS PRECISE ***/
  /* If "this" is passed to QHBoxLayout then
   * the programme stil executes ok, but it generates a message
   * "Attempting to add QLayout". If "this" is removed the message disappers
   * but this begs the question, is this object ever freed from the heap?
   */
  buttonLayout_ = new QHBoxLayout();
  /***/

  buttonLayout_->addWidget( apply_ );
  buttonLayout_->addWidget( cancel_ );

  layout_->addLayout( buttonLayout_, i, 2 );

}

void DefineGameDialog::setCompetitors( const map<QString, int> nCompetitorsMap )
{

  int i = 0;
  competitorLayout_->addWidget(new QLabel("<b>Name</b>", this), i, 0 );
  competitorLayout_->addWidget(new QLabel("<b>Number</b>", this), i, 1 );
  competitorLayout_->addWidget(new QLabel("<b>Color</b>", this), i, 2 );
  ++i;

  int j = 0;
  QWidget* last = 0;
  for ( auto c : nCompetitorsMap ) {
    competitorLabels_.push_back( new QLabel( c.first.toUpper(), this ) );
    competitorNumbers_.push_back( nCompetitorsSpinBox( c.second ) );
    competitorLayout_->addWidget( competitorLabels_.back(), i, 0 );
    competitorLayout_->addWidget( competitorNumbers_.back(), i, 1 );
    competitorLayout_->addWidget( competitorColors_[j], i, 2 );
    competitorLayout_->addWidget( colorButtons_[j], i, 3 );

    if ( last )
      setTabOrder( last, competitorNumbers_.back() );

    last = colorButtons_[j];

    setTabOrder( competitorNumbers_.back(), competitorColors_[j] );
    setTabOrder( competitorColors_[j], colorButtons_[j] );

    i++; j++;
  }

  if ( colorButtons_.size() ) {
    setTabOrder( colorButtons_.back(), apply_ );
    setTabOrder( apply_, cancel_ );
  }

  connect( this, SIGNAL(specificButtonClicked( int ) ),
           this, SLOT( runColorDialog( int ) ) );

  setLayout(layout_);
  iterationsEdit_->setFocus();
}

void DefineGameDialog::setNumberForAllCompetitors( int i )
{
  for ( auto c : competitorNumbers_ ) c->setValue( i );
}

void DefineGameDialog::setCompetitorColors( const map<QString, QColor>& colors )
{
  int i = 0;
  for ( auto c : colors ) {
    QLineEdit* edit = new QLineEdit( c.second.name(), this );
    QFontMetrics metrics(QApplication::font());
    edit->setFixedWidth( metrics.width("mmmmmmmmmmmm") );
    competitorColors_.push_back( edit );

    connect( competitorColors_.back(), SIGNAL( textChanged( QString ) ),
             this, SLOT( setLineEditColor( QString ) ) );

    setLineEditColor( competitorColors_.back() );
    colorButtons_.push_back( new ColorPickButton(i, this) );

    connect( colorButtons_.back(), SIGNAL( clicked() ),
             this, SLOT( colorButtonClicked() ) );

    i++;
  }
}

vector<int> DefineGameDialog::getCompetitors() const
{
  vector <int> nCompetitors;
  for( auto c : competitorNumbers_ )
    nCompetitors.push_back( c->text().toInt() );
  return nCompetitors;
}

map<QString, QColor> DefineGameDialog::getCompetitorColors() const
{
  map<QString, QColor> colors;
  auto it = registeredCompetitors.begin();
  for( auto c : competitorColors_ ) {
    colors[ it->first ] = QColor( c->text() );
    it++;
  }
  return colors;
}


QSpinBox* DefineGameDialog::nCompetitorsSpinBox( int i )
{
  QSpinBox* nCompetitors = new QSpinBox( this );
  nCompetitors->setRange(0, 100);
  nCompetitors->setSingleStep(1);
  nCompetitors->setValue(i);
  return nCompetitors;
}

void DefineGameDialog::colorButtonClicked()
{
  ColorPickButton *button = (ColorPickButton *) sender();
  emit specificButtonClicked( button->getIndex() );
}

void DefineGameDialog::runColorDialog( int i )
{
  QColor color;

  color = QColorDialog::getColor(Qt::green, this);

  if ( color.isValid() )
    competitorColors_[i]->setText(color.name());
}

void DefineGameDialog::setLineEditColor( QLineEdit* edit )
{
  QColor color = QColor( edit->text() );
  if ( color.isValid() ) {
    QPalette pal;
    pal.setColor( QPalette::Text, color );
    edit->setPalette( pal );
    edit->setAutoFillBackground( true );
  }
}

void DefineGameDialog::setLineEditColor( QString )
{
  QLineEdit *edit = (QLineEdit *) sender();
  setLineEditColor( edit );
}
