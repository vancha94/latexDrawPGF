#include "scene.h"
#include <QDebug>
//#include <commands.h>

Scene::Scene(QObject* parent): QGraphicsScene(parent)
{
    sceneMode = NoMode;
    lineItem = 0;
    polylineitem = 0;
    rectItem = 0;
    ellipseItem = 0;
    polygonItem = 0;
    textItem = 0;
    pointItem=0;

    undoStack = new QUndoStack(this);
    undoAction = undoStack->createUndoAction(this);
    redoAction = undoStack->createRedoAction(this);

    border.setColor(QColor("#000000"));
    params.borderColor = "Black";

    background.setColor(QColor("#ffffff"));
    background.setStyle(Qt::SolidPattern);
    params.backgroundCOlor="White";

    firstClick = true;
    isPencilDrawed = false;
    isMoveElemnts = false;
    shiftPressed = false;


    createLineStyles();

    //test code

}

void Scene::setMode(Mode mode)
{
    sceneMode = mode;
    QGraphicsView::DragMode vMode =
            QGraphicsView::NoDrag;
    if(mode != SelectObject && mode != NoMode)
    {
        makeItemsControllable(false);
        vMode = QGraphicsView::NoDrag;
    }
    else if(mode == SelectObject)
    {
        makeItemsControllable(true);
        vMode = QGraphicsView::RubberBandDrag;
        //vMode = QGraphicsView::ScrollHandDrag;
    }

    QGraphicsView* mView = views().at(0);
    if(mView)
        mView->setDragMode(vMode);
}

void Scene::undo()
{
    undoAction->trigger();
    if(!firstClick)
    {
        firstClick = true;
        polygonItem = 0;
        polylineitem =0;
    }
}

void Scene::redo()
{
    redoAction->trigger();
}

void Scene::addText(QGraphicsItem *item)
{
    QString tmpStr;
    AbstractItem *tmpItem = dynamic_cast<AbstractItem*>(item);
    tmpItem->setCooordinats();
    tmpStr=tmpItem->prepareText();
    textStack.push(tmpStr);
}

void Scene::attachStrings()
{
    QString tmpString = "";
    foreach (QString str, textStack)
    {
        if(str!="")
            tmpString+=str + "\n";
    }
    emit transmitText(tmpString);
}

void Scene::addLineStyle(QString str, QPen pen, qreal delta)
{
    QVector<qreal> tmpVector = pen.dashPattern();

    // для "просторных" стилей не видно что. что они более широкие, чем стандартные
    // поэтому для видимости увеличиваем разрыв
    if(delta>0)
        delta*=3;

    for (int i =1; i<tmpVector.size();i+=2)
        tmpVector[i]+=delta;
    //#include <QGraphicsLineItem>
    // обработка ситуации для стиля solid
    // для данного стиля dashPattern() возвращает пустой список
    if (!tmpVector.size())
        tmpVector << 10 << 0;
    listOfLineStyles[str] = tmpVector;
}

void Scene::createLineStyles()
{
    // текстовые константы из LaTeX'а

    // эта константа подобрана экспирементально
    qreal deltaDensity=0.6;

    QPen tmpPen;
    tmpPen.setStyle(Qt::SolidLine);
    addLineStyle("solid",tmpPen);
    params.style = "solid";

    tmpPen.setStyle(Qt::DotLine);
    addLineStyle("dotted",tmpPen);
    addLineStyle("densely dotted",tmpPen,-deltaDensity);
    addLineStyle("loosely dotted",tmpPen,deltaDensity);

    tmpPen.setStyle(Qt::DashLine);
    addLineStyle("dashed",tmpPen);
    addLineStyle("densely dashed",tmpPen,-deltaDensity);
    addLineStyle("loosely dashed",tmpPen,deltaDensity);

    tmpPen.setStyle(Qt::DashDotLine);
    addLineStyle("dashdotted",tmpPen);
    addLineStyle("densely dashdotted",tmpPen,-deltaDensity);
    addLineStyle("loosely dashdotted",tmpPen,deltaDensity);

    tmpPen.setStyle(Qt::DashDotDotLine);
    addLineStyle("dashdotdotted",tmpPen);
    addLineStyle("densely dashdotdotted",tmpPen,-deltaDensity);
    addLineStyle("loosely dashdotdotted",tmpPen,deltaDensity);

}

void Scene::pushStack(QGraphicsItem *item)
{
    addText(item);
    itemStack.push(item);
    attachStrings();
}

void Scene::popStack()
{
    if(sceneMode == DrawPolyLine && polylineitem)
    {

        polylineitem->setCooordinats();
        polylineitem = 0;
        firstClick = true;
    }
    if(sceneMode == DrawPolygon && polygonItem)
    {
        polygonItem->setCooordinats();
        polygonItem = 0;
        firstClick = true;
    }
    if(!itemStack.isEmpty())
        itemStack.pop();
    if(!textStack.empty())
        textStack.pop();
    attachStrings();
}

void Scene::resetText()
{
    textStack.clear();
    foreach (QGraphicsItem* item, itemStack)
    {
        addText(item);
    }
    attachStrings();
}

void Scene::changeBrushItemParams()
{
    if (sceneMode == SelectObject && selectedItems().size())
    {
        ChangeBrushCommand *changeBrush = new ChangeBrushCommand(selectedItems(), background, params);
        connect(changeBrush,&ChangeBrushCommand::useCommand,this,&Scene::resetText);
        undoStack->push(dynamic_cast<QUndoCommand*>(changeBrush));

    }
}

void Scene::setBackgroundColor(QColor color, QString str)
{
    background.setColor(color);
    params.backgroundCOlor = str;

    changeBrushItemParams();

}

void Scene::changePenItemParams()
{
    if(sceneMode == SelectObject && selectedItems().size())
    {
        ChangePenCommand *changePenCommand = new ChangePenCommand(selectedItems(), border, params);
        connect(changePenCommand,&ChangePenCommand::useCommand,this,&Scene::resetText);
        undoStack->push(dynamic_cast<QUndoCommand*>(changePenCommand));
        // resetText();
    }
}

void Scene::setBorderColor(QColor color, QString str)
{
    border.setColor(color);
    params.borderColor = str;
    changePenItemParams();
}

void Scene::setBorderAlpha(int value)
{
    if (value > 255)
        value = 255;
    else if(value < 0)
        value = 0;
    auto tmp  = border.color();
    tmp.setAlpha(value);
    border.setColor(tmp);
    changePenItemParams();
}

void Scene::setBacgroundAlpha(int value)
{
    if (value > 255)
        value = 255;
    else if(value < 0)
        value = 0;
    auto tmp = background.color();
    tmp.setAlpha(value);
    background.setColor(tmp);
    changeBrushItemParams();
}

void Scene::setPenWidth(qreal value)
{
    border.setWidthF(value);
    changePenItemParams();
}

void Scene::setPenStyle(QString str)
{

    border.setDashPattern(listOfLineStyles[str]);
    params.style = str;
    changePenItemParams();
}

void Scene::setPenStyle(QString str, QVector<qreal> vector, qreal offset)
{
    params.style = str;
    border.setDashPattern(vector);
    border.setDashOffset(offset);
    changePenItemParams();
}

void Scene::setJointStyle(QString value, Qt::PenJoinStyle style)
{
    border.setJoinStyle(style);
    params.jointStyle = value;
    changePenItemParams();
}

void Scene::textChanged(QString str, TextItem *item)
{
    TextChanged *command = new TextChanged(item,str,item->toPlainText());
    connect(command,&TextChanged::useCommand,this,&Scene::resetText);
    undoStack->push(dynamic_cast<QUndoCommand*>(command));
}

void Scene::makeItemsControllable(bool areControllable)
{
    foreach(QGraphicsItem* item, items())
    {
        auto tmp = dynamic_cast<AbstractItem*>(item);
        item->setFlag(QGraphicsItem::ItemIsSelectable,areControllable);
        item->setFlag(QGraphicsItem::ItemIsMovable,
                      areControllable);
        if(tmp->isText())
        {
            auto tmpTextItem = dynamic_cast<QGraphicsTextItem*>(item);
            if(sceneMode == DrawText)
                tmpTextItem->setTextInteractionFlags(Qt::TextEditorInteraction);
            else
                tmpTextItem->setTextInteractionFlags(Qt::NoTextInteraction);

        }
    }
}

void Scene::connectSignals()
{

}

void Scene::addPolyLine(QGraphicsSceneMouseEvent *event, bool isPencil)
{
    if(firstClick &&
            ( event->button() == Qt::LeftButton  || event->buttons() == Qt::LeftButton))
    {
        origPoint = event->scenePos();
        firstClick = false;
        polylineitem = new PolyLineItem(isPencil);
        polylineitem->setPen(border,params);


        QUndoCommand* addCommand = new AddCommand(polylineitem);
        addCommandConnectSignal(dynamic_cast<AddCommand*>(addCommand));
        undoStack->push(addCommand);
        pushStack(polylineitem);

        this->addItem(polylineitem);
    }
    else if (!firstClick || (isPencil && event->button() != Qt::RightButton))
    {

        QPolygonF tmpPolygon = polylineitem->polygon();
        tmpPolygon <<event->scenePos();
        polylineitem->setPolygon(tmpPolygon);

        if(event->button() == Qt::RightButton)
        {
            firstClick = true;
            resetText();
            polylineitem = 0;
        }
        if(!isPencil)
            origPoint = event->scenePos();

    }
}

void Scene::addPolygonItem(QGraphicsSceneMouseEvent *event)
{
    if(firstClick &&
            ( event->button() == Qt::LeftButton  || event->buttons() == Qt::LeftButton))
    {
        origPoint = event->scenePos();
        firstClick = false;

        polygonItem = new PolygonItem();
        polygonItem->setPen(border,params);
        polygonItem->setBrush(background,params);

        QUndoCommand* addCommand = new AddCommand(polygonItem);
        addCommandConnectSignal(dynamic_cast<AddCommand*>(addCommand));
        undoStack->push(addCommand);
         pushStack(polygonItem);

        QPolygonF tmpPolygon;
        tmpPolygon << origPoint;
        polygonItem->setPolygon(tmpPolygon);
        this->addItem(polygonItem);
    }
    else if(!firstClick)
    {
        QPolygonF tmpPolygon = polygonItem->polygon();
        tmpPolygon <<event->scenePos();
        polygonItem->setPolygon(tmpPolygon);

        if(event->button() == Qt::RightButton)
        {
            firstClick = true;
          resetText();
            polygonItem = 0;
        }
    }
}

void Scene::addText(QGraphicsSceneMouseEvent *event)
{
    auto tmpList = items(event->scenePos());
    bool textFlag = false;
    if(tmpList.size())
        for(int i =0; i<tmpList.size() && !textFlag ;++i )
        {
            auto tmpItem = dynamic_cast<AbstractItem*>(tmpList[i]);
            textFlag = tmpItem->isText();
        }

    if(!textItem && !textFlag)
    {
        textItem = new TextItem();
        textItem->setPen(border,params);
        textItem->setPos(event->scenePos());
        textItem->setTextInteractionFlags(Qt::TextEditorInteraction);


        QUndoCommand *addCommand = new AddCommand(textItem);
        addCommandConnectSignal(dynamic_cast<AddCommand*>(addCommand));
        undoStack->push(addCommand);

        pushStack(textItem);
        this->addItem(textItem);

    }
    textItem =0;
}

void Scene::addPoint(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        pointItem = new PointItem();
        pointItem->setPen(border,params);
        pointItem->setBrush(background,params);

        QUndoCommand* addCommand = new AddCommand(pointItem);
        addCommandConnectSignal(dynamic_cast<AddCommand*>(addCommand));
        undoStack->push(addCommand);

        pointItem->setRect(event->scenePos());
        this->addItem(pointItem);
        pushStack(pointItem);
    }
}

void Scene::setOjbjectParams(QGraphicsItem *&item)
{
    QUndoCommand *addCommand;

    //    item->setPen(border,params);
    //    item->setBrush(background,params);
    //    item->setPos(origPoint);

    //    addCommand = new AddCommand(item);
    //    addCommandConnectSignal(dynamic_cast<AddCommand*>(addCommand));
    //    undoStack->push(addCommand);
    //    this->addItem(item);

}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(sceneMode == DrawLine ||
            sceneMode == DrawRectangle ||
            sceneMode == DrawEllipse)
    {
        origPoint = event->scenePos();
        if(!firstClick)
            lineItem=0;
        firstClick=true;
    }

    if(sceneMode == DrawPolyLine)
    {
        addPolyLine(event);
    }
    else if(sceneMode ==DrawPencil)
    {
        addPolyLine(event,true);
    }
    else if (sceneMode == DrawPolygon)
    {
        addPolygonItem(event);
    }
    else if (sceneMode == DrawText)
    {
        addText(event);
    }
    else if (sceneMode == DrawPoint)
    {
        addPoint(event);
    }

    QGraphicsScene::mousePressEvent(event);
}

void Scene::addCommandConnectSignal(AddCommand *addCommand)
{
    connect(addCommand,&AddCommand::pushStackItem,this,&Scene::pushStack);
    connect(addCommand,&AddCommand::popStackItem,this,&Scene::popStack);
}

void Scene::addLine(QUndoCommand *addCommand, QGraphicsSceneMouseEvent *event)
{
    if(!lineItem)
    {

        lineItem = new LineItem();
        lineItem->setPen(border,params);

        lineItem->setPos(origPoint);
        addCommand = new AddCommand(lineItem);
        addCommandConnectSignal(dynamic_cast<AddCommand*>(addCommand));
        undoStack->push(addCommand);
        this->addItem(lineItem);
        //setObjectName(lineItem);
    }
    lineItem->setLine(0,0,
                      event->scenePos().x() - origPoint.x(),
                      event->scenePos().y() - origPoint.y());
}


void Scene::addRectangle(QUndoCommand *addCommand, QGraphicsSceneMouseEvent *event)
{
    if(!rectItem)
    {
        rectItem = new Rectangleltem();
        rectItem->setPen(border,params);
        rectItem->setBrush(background,params);
        rectItem->setPos(origPoint);
        addCommand = new AddCommand(rectItem);
        addCommandConnectSignal(dynamic_cast<AddCommand*>(addCommand));
        undoStack->push(addCommand);
        this->addItem(rectItem);

    }
    qreal x =0;
    qreal y =0;
    auto width =event->scenePos().x()-origPoint.x();
    auto height = event->scenePos().y()-origPoint.y();

    if(width < 0)
    {
        x=width;
        width = -width;
    }
    if(height<0)
    {
        y = height;
        height = -height;
    }
    rectItem->setRect(x,y,width,height);
}

void Scene::addPencil(QGraphicsSceneMouseEvent *event)
{
    if(!firstClick)
    {
        addPolyLine(event,true);
        origPoint = event->scenePos();
        isPencilDrawed = true;
    }
}

// TODO: отрефакторить так, чтобы небыло повторяющегося поведения в добавлении элементов (чтобы все было в одном методе)

void Scene::addElipse(QUndoCommand *addCommand, QGraphicsSceneMouseEvent *event)
{
    if(!ellipseItem)
    {
        ellipseItem = new EllipseItem();
        ellipseItem->setPen(border,params);
        ellipseItem->setBrush(background,params);
        ellipseItem->setPos(origPoint);
        addCommand = new AddCommand(ellipseItem);
        addCommandConnectSignal(dynamic_cast<AddCommand*>(addCommand));
        undoStack->push(addCommand);
        this->addItem(ellipseItem);
    }
    qreal x =0;
    qreal y =0;
    auto width =event->scenePos().x()-origPoint.x();
    auto height = event->scenePos().y()-origPoint.y();

    if(width < 0)
    {
        x=width;
        width = -width;
    }
    if(height<0)
    {
        y = height;
        height = -height;
    }
    ellipseItem->setRect(x,y,width,height);
}

void Scene::drawPolygon(QGraphicsSceneMouseEvent *event)
{
    if(!firstClick)
    {
        auto tmpPolygon = polygonItem->polygon();
        if(polygonItem->polygon().size()>1)
            tmpPolygon.removeLast();
        tmpPolygon << event->scenePos();
        polygonItem->setPolygon(tmpPolygon);
    }
}

void Scene::drawPolyline(QGraphicsSceneMouseEvent *event)
{
    auto tmpPolygon = polylineitem->polygon();
    if(polylineitem->polygon().size()>1)
        tmpPolygon.removeLast();
    tmpPolygon << event->scenePos();
    polylineitem->setPolygon(tmpPolygon);
}

void Scene::checkShiftPress(QGraphicsSceneMouseEvent *event)
{

    double k = (double)(event->scenePos().y()-origPoint.y())/
               (event->scenePos().x()-origPoint.x());
    if(shiftPressed && (sceneMode == DrawLine ||
                        sceneMode == DrawPolyLine))
    {

        auto tmp = event->scenePos() - origPoint;
        if(fabs(k)>M_PI/4  )
        {
            QCursor::setPos(event->screenPos()-QPoint(tmp.x(),0));
        }
        else if(fabs(k)<=M_PI/4)
        {
            QCursor::setPos(event->screenPos()-QPoint(0,tmp.y()));
        }
    }
    else if(shiftPressed &&
            (sceneMode == DrawEllipse ||
             sceneMode == DrawRectangle))
    {
        auto tmp  = event->screenPos();
        auto tmpDelta = event->scenePos() - origPoint;
        if(k>0 )
       {
        tmp.setY(tmp.y() - tmpDelta.y()+tmpDelta.x());
        QCursor::setPos(tmp.x(),tmp.y());
       }
       else if (k<0)
       {
            if(tmpDelta.x()>0 && tmpDelta.y()<0)
                tmp.setY(tmp.y() + fabs(tmpDelta.y())-fabs(tmpDelta.x()));
            else if (tmpDelta.x()<0 && tmpDelta.y()>0)
                tmp.setY(tmp.y() - tmpDelta.y()+fabs(tmpDelta.x()));

           QCursor::setPos(tmp.x(),tmp.y());
       }
    }
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QUndoCommand *addCommand;
    if (sceneMode == DrawPolyLine)
    {
        if(!firstClick)
        {
            drawPolyline(event);
        }
    }
    else if(sceneMode == DrawPolygon)
    {
        drawPolygon(event);
    }
    if( event->buttons() & Qt::LeftButton)
    {
        if(sceneMode == DrawLine)
        {
            addLine(addCommand, event);
        }
        else if (sceneMode == DrawPencil)
        {
            addPencil(event);
        }
        else if (sceneMode == DrawRectangle)
        {
            addRectangle(addCommand, event);
        }
        else  if (sceneMode == DrawEllipse)
        {
            addElipse(addCommand, event);
        }
    }
    if(sceneMode == SelectObject && !isMoveElemnts &&
            !selectedItems().isEmpty())
    {
        movingsElementsStart();
    }

    checkShiftPress(event);
    QGraphicsScene::mouseMoveEvent(event);
}

void Scene::movingsElementsStart()
{
    oldPos.clear();
    newPos.clear();
    isMoveElemnts = true;
    foreach (QGraphicsItem *item, selectedItems())
    {
        oldPos << item->pos();
    }
}

void Scene::movingElementsEnd()
{
    if(isMoveElemnts)
    {
        auto tmpList = selectedItems();
        foreach (QGraphicsItem *item, tmpList)
        {
            newPos << item->pos();
        }
        if( !newPos.isEmpty() &&
                !oldPos.isEmpty())
        {
            if(oldPos.first() != newPos.first() &&
                    oldPos.size() == newPos.size())
            {
                MoveCommand *moveCommand = new MoveCommand(tmpList,oldPos,newPos);
                //  qDebug() << oldPos << newPos;
                connect(moveCommand,&MoveCommand::useCommand,this,&Scene::resetText);
                undoStack->push(dynamic_cast<QUndoCommand*>(moveCommand));
            }
        }
        isMoveElemnts = false;
    }
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(sceneMode == DrawLine)
    {
        if(lineItem)
            pushStack(lineItem);
        lineItem=0;
    }
    else if(sceneMode == SelectObject)
    {
        movingElementsEnd();
    }
    else if(sceneMode == DrawPencil)
    {
        if(event->button() != Qt::RightButton && isPencilDrawed)
        {
            firstClick = true;
            pushStack(polylineitem);
            polylineitem=0;
            //    lineItem = 0;
            isPencilDrawed = false;
        }
        if(!isPencilDrawed)
            firstClick = true;
    }
    else if(sceneMode == DrawRectangle)
    {
        if(rectItem)
            pushStack(rectItem);
        rectItem = 0;
    }
    else if(sceneMode == DrawEllipse)
    {
        if(ellipseItem)
            pushStack(ellipseItem);
        ellipseItem = 0;
    }
    //    else if(sceneMode == DrawText)
    //        textItem = 0;
    QGraphicsScene::mouseReleaseEvent(event);
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Delete ||
            event->key() == Qt::Key_Backspace)
    {
        auto tmpList = selectedItems();
        if(tmpList.size())
        {
            DeleteCommand *deleteCommand = new DeleteCommand(tmpList);
            connect(deleteCommand,&DeleteCommand::useCommand,this,&Scene::resetText);
            undoStack->push(dynamic_cast<QUndoCommand*>(deleteCommand));
        }
    }
    else if(event->matches(QKeySequence::Undo))
    {
        undoAction->trigger();
    }
    else if(event->matches(QKeySequence::Redo))
    {
        redoAction->trigger();
    }
    else if (event->key() == Qt::Key_Shift)
    {
        shiftPressed = true;
    }
    else if(event->matches(QKeySequence::SelectAll) &&
            sceneMode == SelectObject)
    {
        foreach (QGraphicsItem* item, items())
        {
            item->setSelected(true);
        }
    }

    QGraphicsScene::keyPressEvent(event);
}

void Scene::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Shift)
        shiftPressed = false;

    if(sceneMode == DrawText)
        resetText();
}
