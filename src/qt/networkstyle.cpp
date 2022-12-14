// Copyright (c) 2014-2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <qt/networkstyle.h>

#include <qt/guiconstants.h>

#include <QApplication>

static const struct {
    const char *networkId;
    const char *appName;
    const int iconColorHueShift;
    const int iconColorSaturationReduction;
    const char *titleAddText;
} network_styles[] = {
    {"main", QAPP_APP_NAME_DEFAULT, 0, 0, ""},
    {"test", QAPP_APP_NAME_TESTNET, 0, 0, QT_TRANSLATE_NOOP("SplashScreen", "[testnet]")},
    {"regtest", QAPP_APP_NAME_TESTNET, 60, 1, "[regtest]"}
};
static const unsigned network_styles_count = sizeof(network_styles)/sizeof(*network_styles);

// titleAddText needs to be const char* for tr()
NetworkStyle::NetworkStyle(const QString &_appName, const int iconColorHueShift, const int iconColorSaturationReduction, const char *_titleAddText):
    appName(_appName),
    titleAddText(qApp->translate("SplashScreen", _titleAddText))
{
    // load pixmap
    QPixmap appIconPixmap(":/icons/bitcoin");
    QPixmap splashImagePixmap(":/icons/maza_splash");

    if(iconColorHueShift != 0 && iconColorSaturationReduction != 0)
    {
        // generate QImage from QPixmap
        QImage appIconImg = appIconPixmap.toImage();
        QImage splashImageImg = splashImagePixmap.toImage();

        int h,s,l,a;

        // traverse though lines
        for(int y=0;y<appIconImg.height();y++)
        {
            QRgb *scL = reinterpret_cast< QRgb *>( appIconImg.scanLine( y ) );

            // loop through pixels
            for(int x=0;x<appIconImg.width();x++)
            {
                // preserve alpha because QColor::getHsl doesn't return the alpha value
                a = qAlpha(scL[x]);
                QColor col(scL[x]);

                // get hue value
                col.getHsl(&h,&s,&l);

                // rotate color on RGB color circle
                // 70° should end up with the typical "testnet" green
                h+=iconColorHueShift;

                // change saturation value
                if(s>iconColorSaturationReduction)
                {
                    s -= iconColorSaturationReduction;
                }
                col.setHsl(h,s,l,a);

                // set the pixel
                scL[x] = col.rgba();
            }
        }
		for(int y=0;y<splashImageImg.height();y++)
        {
            QRgb *scL = reinterpret_cast< QRgb *>( splashImageImg.scanLine( y ) );

            // loop through pixels
            for(int x=0;x<splashImageImg.width();x++)
            {
                // preserve alpha because QColor::getHsl doesn't return the alpha value
                a = qAlpha(scL[x]);
                QColor col(scL[x]);

                // get hue value
                col.getHsl(&h,&s,&l);

                // rotate color on RGB color circle
                // 70° should end up with the typical "testnet" green
                h+=iconColorHueShift;

                // change saturation value
                if(s>iconColorSaturationReduction)
                {
                    s -= iconColorSaturationReduction;
                }
                col.setHsl(h,s,l,a);

                // set the pixel
                scL[x] = col.rgba();
            }
        }

        //convert back to QPixmap
#if QT_VERSION >= 0x040700
		appIconPixmap.convertFromImage(appIconImg);
        splashImagePixmap.convertFromImage(splashImageImg);
#else
        appIconPixmap = QPixmap::fromImage(appIconImg);
        splashImagePixmap = QPixmap::fromImage(splashImageImg);
#endif
    }

    appIcon             = QIcon(appIconPixmap);
    trayAndWindowIcon   = QIcon(appIconPixmap.scaled(QSize(256,256)));
    splashImage         = splashImagePixmap;
}

const NetworkStyle *NetworkStyle::instantiate(const QString &networkId)
{
    for (unsigned x=0; x<network_styles_count; ++x)
    {
        if (networkId == network_styles[x].networkId)
        {
            return new NetworkStyle(
                    network_styles[x].appName,
                    network_styles[x].iconColorHueShift,
                    network_styles[x].iconColorSaturationReduction,
                    network_styles[x].titleAddText);
        }
    }
    return 0;
}
