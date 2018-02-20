#include "imgoperate.h"

ImgOperate::ImgOperate()
{
    Square default_square = {QPoint(10,10), QPoint(100,10), QPoint(100,100), QPoint(10,100)};
    squares.push_back(default_square);
    it = squares.begin();
    CurrentSquare() = *it;
}

Square& ImgOperate::CurrentSquare() {
    return current_square;
}

const Square& ImgOperate::CurrentSquare() const {
    return current_square;
}

Square ImgOperate::NextSquare() {
    it++;
    if (it == squares.end()) it = squares.begin();
    CurrentSquare() = *it;
    return CurrentSquare();
}

Square ImgOperate::PreviousSquare() {
    if (it == squares.begin()) it = squares.end();
    it--;
    CurrentSquare() = *it;
    return CurrentSquare();
}

int ImgOperate::LoadMainImage(QString fileName) {
    int _result;
    initialize();
    _result = loadImage(fileName, main_image);
    process();
    return _result;
}

int ImgOperate::LoadReplaceImage(QString fileName) {
    int _result;
    _result = loadImage(fileName, replace_image);
    return _result;
}

QPixmap ImgOperate::GetCanvas() {
    refreshCanvas();
    cv::cvtColor(canvas, canvas_output, CV_BGR2RGB);
    return QPixmap::fromImage(
                QImage(
                    canvas_output.data,
                    canvas_output.cols,
                    canvas_output.rows,
                    canvas_output.step,
                    QImage::Format_RGB888
                    )
                );
}

int ImgOperate::SaveImage(QString fileName) {
    return cv::imwrite(fileName.toStdString(), canvas);
}

bool ImgOperate::IsEmpty() {
    return main_image.empty();
}

void ImgOperate::initialize() {
    squares.clear();
    main_image.release();
    canvas.release();
    canvas_output.release();
    replace_image.release();
    replace_image_transformed.release();
}

int ImgOperate::loadImage(QString fileName, cv::Mat& mat) {
    if (fileName.isNull()) {
        return -1;
    }
    mat = cv::imread(fileName.toStdString());
    if (mat.empty()) {
        return -1;
    }
    return 0;
}

double ImgOperate::angle(cv::Point pt1, cv::Point pt2, cv::Point pt0) {
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2) / sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

void ImgOperate::detectSquares() {
    std::vector<std::vector<cv::Point>> _squares;
    std::vector<std::vector<cv::Point>> contours;
    cv::Mat blurred(main_image.size(), CV_8UC3);
    cv::medianBlur(main_image, blurred, 9);
    cv::Mat gray0(blurred.size(), CV_8U), gray;
    for (int c = 0; c < 3; c++) {
        int ch[] = { c, 0 };
        cv::mixChannels(&blurred, 1, &gray0, 1, ch, 1);
        const int threshold_level = 2;
        for (int l = 0; l < threshold_level; l++) {
            if (l == 0) {
                cv::Canny(gray0, gray, 10, 20, 3);
                cv::dilate(gray, gray, cv::Mat(), cv::Point(-1, -1));
            } else {
                gray = gray0 >= (l + 1) * 255 / threshold_level;
            }

            cv::findContours(gray, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

            std::vector<cv::Point> approx;
            for (size_t i = 0; i < contours.size(); i++) {
                cv::approxPolyDP(cv::Mat(contours[i]), approx, cv::arcLength(cv::Mat(contours[i]), true)*0.02, true);
                if (approx.size() == 4 &&
                    fabs(cv::contourArea(cv::Mat(approx))) > 1000 &&
                    cv::isContourConvex(cv::Mat(approx))) {
                    double maxCosine = 0;

                    for (int j = 2; j < 5; j++) {
                        double cosine = fabs(angle(approx[j % 4], approx[j - 2], approx[j - 1]));
                        maxCosine = MAX(maxCosine, cosine);
                    }

                    if (maxCosine < 0.3)
                        _squares.push_back(approx);
                }
            }
        }
    }
    if (_squares.empty()) {
        Square default_square;
        default_square.push_back(QPoint(0, 0));
        default_square.push_back(QPoint(0, main_image.rows - 1));
        default_square.push_back(QPoint(main_image.cols - 1, main_image.rows - 1));
        default_square.push_back(QPoint(main_image.cols - 1, 0));
        squares.push_back(default_square);
    }

    for (auto& square_cv : _squares) {
        Square square;
        for (auto& point : square_cv) {
            square.push_back(QPoint(point.x, point.y));
        }
        squares.push_back(square);
    }
}

int ImgOperate::process() {
    detectSquares();
    it = squares.begin();
    current_square = *it;
    return 0;
}

int ImgOperate::refreshCanvas() {
    main_image.copyTo(canvas);
    if (!replace_image.empty()) {
        replace();
    }
    return 0;
}

int ImgOperate::replace() {
    replace_image_transformed = cv::Mat(canvas.size(), CV_8UC4);

    std::vector<cv::Point2f> src = {
        cv::Point2f(0, 0),
        cv::Point2f(0, replace_image.rows - 1),
        cv::Point2f(replace_image.cols - 1, replace_image.rows - 1),
        cv::Point2f(replace_image.cols - 1, 0)
        };

    std::vector<cv::Point2f> dst = {
        cv::Point2f(CurrentSquare()[0].x(), CurrentSquare()[0].y()),
        cv::Point2f(CurrentSquare()[1].x(), CurrentSquare()[1].y()),
        cv::Point2f(CurrentSquare()[2].x(), CurrentSquare()[2].y()),
        cv::Point2f(CurrentSquare()[3].x(), CurrentSquare()[3].y()),
    };

    cv::Mat transform = cv::getPerspectiveTransform(src, dst);
    cv::warpPerspective(replace_image, replace_image_transformed, transform, replace_image_transformed.size());
    std::vector<cv::Mat> replace_image_transformed_channels;
    cv::split(replace_image_transformed, replace_image_transformed_channels);
    replace_image_transformed.copyTo(canvas, replace_image_transformed_channels[0]);
    return 0;
}
