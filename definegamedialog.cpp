#include <QtGui>
#include "definegamedialog.h"
#include "competitor.h"

DefineGameDialog::DefineGameDialog(QWidget* parent)
  : QDialog(parent)
{
  setWindowTitle( tr("Define Game Dialog") );
  resize( 700, 300 );

  int i = 0;

  layout_ = new QGridLayout;

  apply_ = new QPushButton( tr("&Apply"), this );
  connect(apply_, SIGNAL(clicked()), this, SLOT(accept()));
  cancel_ = new QPushButton(tr("&Cancel"));
  connect(cancel_, SIGNAL(clicked()), this, SLOT(reject()));

  iterationsLabel_ = new QLabel(tr("Iterations"));
  iterationsEdit_ = new QSpinBox;
  iterationsEdit_->setRange(1, 999999999);
  iterationsEdit_->setSingleStep(100);
  iterationsEdit_->setValue(1000);
  iterationsLabel_->setBuddy(iterationsEdit_);

  layout_->addWidget( iterationsLabel_, i, 0 );
  layout_->addWidget( iterationsEdit_, i, 1 );
  ++i;

  randomSeedLabel_ = new QLabel(tr("Random seed"));
  randomSeedEdit_ = new QSpinBox;
  randomSeedEdit_->setRange( 1, 999999999);
  randomSeedEdit_->setSingleStep(1);
  randomSeedEdit_->setValue( 1000 );
  randomSeedLabel_->setBuddy( randomSeedEdit_ );

  layout_->addWidget( randomSeedLabel_, i, 0 );
  layout_->addWidget( randomSeedEdit_, i, 1 );
  ++i;

  updateStyleLabel_ = new QLabel( tr("Update style") );
  updateStyleCombo_ = new QComboBox;
  updateStyleCombo_->addItem(tr("ratio"));
  updateStyleCombo_->addItem(tr("ratio with lowest set to 0"));
  updateStyleCombo_->addItem(tr("rank"));
  updateStyleLabel_->setBuddy(updateStyleCombo_);

  layout_->addWidget( updateStyleLabel_, i, 0 );
  layout_->addWidget( updateStyleCombo_, i, 1 );
  ++i;

  updateFrequencyLabel_ = new QLabel( tr("Update frequency") );
  updateFrequencyEdit_ = new QSpinBox;
  updateFrequencyEdit_->setRange(1, 999999999);
  updateFrequencyEdit_->setSingleStep(10);
  updateFrequencyEdit_->setValue(1);
  updateFrequencyLabel_->setBuddy(updateStyleCombo_);

  layout_->addWidget( updateFrequencyLabel_, i, 0 );
  layout_->addWidget( updateFrequencyEdit_, i, 1 );
  ++i;

  competitorLayout_ = new QGridLayout;

  layout_->addLayout( competitorLayout_, i, 0, 1, 4 );
  ++i;

  layout_->addWidget( apply_, i , 1 );
  layout_->addWidget( cancel_, i, 2 );

}

void DefineGameDialog::setCompetitors( const map<QString, int> nCompetitorsMap )
{

  int i = 0;
  competitorLayout_->addWidget(new QLabel("<b>Name</b>"), i, 0 );
  competitorLayout_->addWidget(new QLabel("<b>Number</b>"), i, 1 );
  competitorLayout_->addWidget(new QLabel("<b>Color</b>"), i, 2 );
  ++i;

  int j = 0;
  for ( auto c : nCompetitorsMap ) {
    competitorLabels_.push_back( new QLabel( c.first.toUpper() ) );
    competitorNumbers_.push_back( nCompetitorsSpinBox( c.second ) );
    competitorLayout_->addWidget( competitorLabels_.back(), i, 0 );
    competitorLayout_->addWidget( competitorNumbers_.back(), i, 1 );
    competitorLayout_->addWidget( competitorColors_[j], i, 2 );
    competitorLayout_->addWidget( colorButtons_[j], i, 3 );
    connect( competitorColors_[j], SIGNAL( textChanged( QString ) ),
             this, SLOT( setLineEditColor( QString ) ) );
    connect( colorButtons_[ j ], SIGNAL( clicked() ),
             this, SLOT( colorButtonClicked() ) );

    i++; j++;
  }
  connect( this, SIGNAL(specificButtonClicked( int ) ),
           this, SLOT( runColorDialog( int ) ) );

  setLayout(layout_);
}

void DefineGameDialog::setCompetitorColors( const map<QString, QColor>& colors )
{
  int i = 0;
  for ( auto c : colors ) {
    QLineEdit* edit = new QLineEdit( c.second.name(), this );
    QFontMetrics metrics(QApplication::font());
    edit->setFixedWidth( metrics.width("mmmmmmmmmmmm") );
    competitorColors_.push_back( edit );
    colorButtons_.push_back( new ColorPickButton(i, this) );
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
  QSpinBox* nCompetitors = new QSpinBox;
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

void DefineGameDialog::setLineEditColor( QString )
{
  qDebug() << "Got here";
  QLineEdit *edit = (QLineEdit *) sender();
  QColor color = QColor( edit->text() );
  if ( color.isValid() ) {
    QPalette pal;
    pal.setColor( QPalette::Text, color );
    edit->setPalette( pal );
    edit->setAutoFillBackground( true );
  }
}
