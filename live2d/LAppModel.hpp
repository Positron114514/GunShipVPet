/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#pragma once

#include <CubismFramework.hpp>
#include <Model/CubismUserModel.hpp>
#include <ICubismModelSetting.hpp>
#include <Type/csmRectF.hpp>
#include <Rendering/OpenGL/CubismOffscreenSurface_OpenGLES2.hpp>
// #include "ModelAPI.hpp"
#include "LAppWavFileHandler.hpp"

/**
 * @brief ユーザーが実際に使用するモデルの実装クラス<br>
 *         モデル生成、機能コンポーネント生成、更新処理とレンダリングの呼び出しを行う。
 *
 */
class LAppModel : public Csm::CubismUserModel
{
public:
    /**
     * @brief コンストラクタ
     */
    LAppModel();

    /**
     * @brief デストラクタ
     *
     */
    virtual ~LAppModel();

    /**
     * @brief model3.jsonが置かれたディレクトリとファイルパスからモデルを生成する
     *
     */
    void LoadAssets(const Csm::csmChar* dir, const  Csm::csmChar* fileName);

    /**
     * @brief LAppModel::ResetModel 重置模型
     * @param model MoldeAPI::Model, 即存放model信息的函数
     */
    // void LAppModel::ResetModel(ModelAPI::Model *model);

    /**
     * @brief レンダラを再構築する
     *
     */
    void ReloadRenderer();

    /**
     * @brief   モデルの更新処理。モデルのパラメータから描画状態を決定する。
     *
     */
    void Update();

    /**
     * @brief   モデルを描画する処理。モデルを描画する空間のView-Projection行列を渡す。
     *
     * @param[in]  matrix  View-Projection行列
     */
    void Draw(Csm::CubismMatrix44& matrix);

    /**
     * @brief   引数で指定したモーションの再生を開始する。
     *
     * @param[in]   group                       モーショングループ名
     * @param[in]   no                          グループ内の番号
     * @param[in]   priority                    優先度
     * @param[in]   onFinishedMotionHandler     モーション再生終了時に呼び出されるコールバック関数。NULLの場合、呼び出されない。
     * @return                                  開始したモーションの識別番号を返す。個別のモーションが終了したか否かを判定するIsFinished()の引数で使用する。開始できない時は「-1」
     */
    Csm::CubismMotionQueueEntryHandle StartMotion(const Csm::csmChar* group, Csm::csmInt32 no, Csm::csmInt32 priority, Csm::ACubismMotion::FinishedMotionCallback onFinishedMotionHandler = NULL);

    /**
     * @brief   ランダムに選ばれたモーションの再生を開始する。
     *
     * @param[in]   group                       モーショングループ名
     * @param[in]   priority                    優先度
     * @param[in]   onFinishedMotionHandler     モーション再生終了時に呼び出されるコールバック関数。NULLの場合、呼び出されない。
     * @return                                  開始したモーションの識別番号を返す。個別のモーションが終了したか否かを判定するIsFinished()の引数で使用する。開始できない時は「-1」
     */
    Csm::CubismMotionQueueEntryHandle StartRandomMotion(const Csm::csmChar* group, Csm::csmInt32 priority, Csm::ACubismMotion::FinishedMotionCallback onFinishedMotionHandler = NULL);

    /**
     * @brief   引数で指定した表情モーションをセットする
     *
     * @param   expressionID    表情モーションのID
     */
    void SetExpression(const Csm::csmChar* expressionID);

    /**
     * @brief   ランダムに選ばれた表情モーションをセットする
     *
     */
    void SetRandomExpression();

    /**
    * @brief   イベントの発火を受け取る
    *
    */
    virtual void MotionEventFired(const Live2D::Cubism::Framework::csmString& eventValue);

    /**
     * @brief    当たり判定テスト。<br>
     *            指定IDの頂点リストから矩形を計算し、座標が矩形範囲内か判定する。
     *
     * @param[in]   hitAreaName     当たり判定をテストする対象のID
     * @param[in]   x               判定を行うX座標
     * @param[in]   y               判定を行うY座標
     */
    virtual Csm::csmBool HitTest(const Csm::csmChar* hitAreaName, Csm::csmFloat32 x, Csm::csmFloat32 y);

    /**
     * @brief   別ターゲットに描画する際に使用するバッファの取得
     */
    Csm::Rendering::CubismOffscreenSurface_OpenGLES2& GetRenderBuffer();

    /**
     * @brief   .moc3ファイルの整合性をチェックする
     *
     * @param[in]   mocName MOC3ファイル名
     * @return      MOC3に整合性があれば'true'、そうでなければ'false'。
     */
    Csm::csmBool HasMocConsistencyFromFile(const Csm::csmChar* mocFileName);


    // Custom
    bool isMouseOnModel(Csm::csmFloat32 x, Csm::csmFloat32 y);

    static LAppModel* GetInstance()
    {
        if(instance == nullptr)
            instance = new LAppModel;
        return instance;
    }

protected:
    /**
     *  @brief  モデルを描画する処理。モデルを描画する空間のView-Projection行列を渡す。
     *
     */
    void DoDraw();

private:
    /**
     * @brief model3.jsonからモデルを生成する。<br>
     *         model3.jsonの記述に従ってモデル生成、モーション、物理演算などのコンポーネント生成を行う。
     *
     * @param[in]   setting     ICubismModelSettingのインスタンス
     *
     */
    void SetupModel(Csm::ICubismModelSetting* setting);

    /**
     * @brief OpenGLのテクスチャユニットにテクスチャをロードする
     *
     */
    void SetupTextures();

    /**
     * @brief   モーションデータをグループ名から一括でロードする。<br>
     *           モーションデータの名前は内部でModelSettingから取得する。
     *
     * @param[in]   group  モーションデータのグループ名
     */
    void PreloadMotionGroup(const Csm::csmChar* group);

    /**
     * @brief   モーションデータをグループ名から一括で解放する。<br>
     *           モーションデータの名前は内部でModelSettingから取得する。
     *
     * @param[in]   group  モーションデータのグループ名
     */
    void ReleaseMotionGroup(const Csm::csmChar* group) const;

    /**
    * @brief すべてのモーションデータの解放
    *
    * すべてのモーションデータを解放する。
    */
    void ReleaseMotions();

    /**
    * @brief すべての表情データの解放
    *
    * すべての表情データを解放する。
    */
    void ReleaseExpressions();

    // 将注释改成了中文, 玛德看不懂
    Csm::ICubismModelSetting* _modelSetting; ///< 模型设定信息
    Csm::csmString _modelHomeDir; ///< 存放模型设定的目录
    Csm::csmFloat32 _userTimeSeconds; ///< 时间差的累积值[秒]
    Csm::csmVector<Csm::CubismIdHandle> _eyeBlinkIds; ///< 模型设定的眨眼功能参数ID
    Csm::csmVector<Csm::CubismIdHandle> _lipSyncIds; ///< 模型设定的嘴唇同步功能参数ID
    Csm::csmMap<Csm::csmString, Csm::ACubismMotion*> _motions; ///< 已加载动作的列表
    Csm::csmMap<Csm::csmString, Csm::ACubismMotion*> _expressions; ///< 已加载表情的列表
    Csm::csmVector<Csm::csmRectF> _hitArea; ///< 点击区域
    Csm::csmVector<Csm::csmRectF> _userArea; ///< 用户区域
    const Csm::CubismId* _idParamAngleX; ///< 参数ID: ParamAngleX
    const Csm::CubismId* _idParamAngleY; ///< 参数ID: ParamAngleX
    const Csm::CubismId* _idParamAngleZ; ///< 参数ID: ParamAngleX
    const Csm::CubismId* _idParamBodyAngleX; ///< 参数ID: ParamBodyAngleX
    const Csm::CubismId* _idParamEyeBallX; ///< 参数ID: ParamEyeBallX
    const Csm::CubismId* _idParamEyeBallY; ///< 参数ID: ParamEyeBallXY

    LAppWavFileHandler _wavFileHandler; ///< wav文件处理程序

    Csm::Rendering::CubismOffscreenSurface_OpenGLES2 _renderBuffer; ///< 非帧缓冲绘制目标

    inline static LAppModel *instance = nullptr;
};
