// --------------------------------------------------------------------------
//                   OpenMS -- Open-Source Mass Spectrometry
// --------------------------------------------------------------------------
// Copyright The OpenMS Team -- Eberhard Karls University Tuebingen,
// ETH Zurich, and Freie Universitaet Berlin 2002-2015.
//
// This software is released under a three-clause BSD license:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of any author or any participating institution
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
// For a full list of authors, refer to the file AUTHORS.
// --------------------------------------------------------------------------
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL ANY OF THE AUTHORS OR THE CONTRIBUTING
// INSTITUTIONS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// --------------------------------------------------------------------------
// $Maintainer: Chris Bielow $
// $Authors: Chris Bielow $
// --------------------------------------------------------------------------

#include <OpenMS/VISUAL/MISC/Helpers.h>

#include <QDesktopServices>
#include <QDir>
#include <QUrl>
#include <QMessageBox>
#include <QString>


namespace OpenMS
{

  void Helpers::openFolder(const QString& folder)
  {
#if defined(__APPLE__)
    QProcess* p = new QProcess();
    p->setProcessChannelMode(QProcess::ForwardedChannels);
    QStringList app_args;
    app_args.append(path);
    p->start("/usr/bin/open", app_args);
    if (!p->waitForStarted())
    {
      // execution failed
      QMessageBox::warning(0, "Open Folder Error", "The folder '" + path + "' could not be opened!");
      LOG_ERROR << "Failed to open folder '" << path.toStdString() << "'" << std::endl;
      LOG_ERROR << p->errorString().toStdString() << std::endl;
    }
#else
    if (!QDir(folder).exists() || (!QDesktopServices::openUrl(QUrl("file:///" + folder, QUrl::TolerantMode))))
    {
      QMessageBox::warning(0, "Open Folder Error", "The folder '" + folder + "' could not be opened!");
    }
#endif
  }

} //namespace OpenMS
