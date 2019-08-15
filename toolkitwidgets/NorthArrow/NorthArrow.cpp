#include "NorthArrow.h"
#include "NorthArrowController.h"

#include <QMouseEvent>

NorthArrow::NorthArrow(QWidget* parent) :
  QLabel(parent),
  m_controller(new NorthArrowController(this))
{
  Q_INIT_RESOURCE(images);
  m_image = QPixmap(":/images/compass.png");

  if (!m_image.isNull())
  {
    this->setPixmap(m_image);
  }

  connect(m_controller, &NorthArrowController::rotationChanged, this, [this]()
  {
    if (m_image.isNull())
      return;

    QMatrix rm;
    rm.rotate(-m_controller->rotation());
    const int imageWidth = m_image.width();
    const int imageHeight = m_image.height();
    auto pix = m_image.transformed(rm, Qt::SmoothTransformation);
    pix = pix.copy((pix.width() - imageWidth)/2, (pix.height() - imageHeight)/2, imageWidth, imageHeight);

    this->setPixmap(pix);
  });
}

NorthArrow::~NorthArrow()
{
}

void NorthArrow::setMapView(Esri::ArcGISRuntime::MapGraphicsView* mapView)
{
  m_controller->setMapView(mapView);
}

void NorthArrow::mouseDoubleClickEvent(QMouseEvent* event)
{
  m_controller->resetRotation();
  event->accept();
}
