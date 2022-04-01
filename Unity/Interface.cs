namespace CoCInterface
{
    public interface IUnit
    {
        // 유닛 정보
        string uInfo {get; set;}
        // 유닛 이름
        string uName {get; set;}
        // 유닛 체력
        int uHp {get; set;}
        // 유닛 공격력
        int uDamage {get; set;}
        // 유닛 가격
        int uPrice {get; set;}
        // 이동속도
        float uMoveSpeed {get; set;}
        // 공격속도
        float uAttackSpeed {get; set;}
        // 개발시간
        float uDevelopmentTime {get; set;}
        // 업그레이드 비용
        int uUpgradePrice {get; set;}
        // 업그레이드 시간
        float uUpgradeTime {get; set;}
        // 최대 업그레이드
        int uMaxUpgrade {get; set;}
        // 인구수
        int uPopulation {get; set;}
        // 레벨(업그레이드 레벨)
        int uLevel {get; set;}
        // 언락시기
        int uUnlock {get; set;}                                                                                                                                                                                                                                                                                             

    }

    public interface IBuilding
    {
        // 건물 정보
        string bInfo {get; set;}
        // 건물 이름
        string bName {get; set;}
        // 건물 체력
        int bHp {get; set;}
        // 건물 가격
        int bPrice {get; set;}
        // 건물 건설시간
        float bDevelopmentTime {get; set;}
        // 건물 업그레이드 가격
        int bUpgradePrice {get; set;}
        // 업그레이드 시간
        float bUpgradeTime {get; set;}
        // 건물 최대 개수
        int bMaxCount {get; set;}
        // 레벨(업그레이드 레벨)
        int bLevel {get; set;}
    }

    public class tUnitInfo : IUnit
    {
        // 유닛 정보
        public string uInfo {get; set;}
        // 유닛 이름
        public string uName {get; set;}
        // 유닛 체력
        public int uHp {get; set;}
        // 유닛 공격력
        public int uDamage {get; set;}
        // 유닛 가격
        public int uPrice {get; set;}
        // 이동속도
        public float uMoveSpeed {get; set;}
        // 공격속도
        public float uAttackSpeed {get; set;}
        // 개발시간
        public float uDevelopmentTime {get; set;}
        // 업그레이드 비용
        public int uUpgradePrice {get; set;}
        // 업그레이드 시간
        public float uUpgradeTime {get; set;}
        // 최대 업그레이드
        public int uMaxUpgrade {get; set;}
        // 인구수
        public int uPopulation {get; set;}
        // 레벨(업그레이드 레벨)
        public int uLevel {get; set;}
        // 언락시기
        public int uUnlock {get; set;}
    }

    public class tBuildingInfo : IBuilding
    {
        // 건물 정보
        public string bInfo {get; set;}
        // 건물 이름
        public string bName {get; set;}
        // 건물 체력
        public int bHp {get; set;}
        // 건물 가격
        public int bPrice {get; set;}
        // 건물 건설시간
        public float bDevelopmentTime {get; set;}
        // 건물 업그레이드 가격
        public int bUpgradePrice {get; set;}
        // 업그레이드 시간
        public float bUpgradeTime {get; set;}
        // 건물 최대 개수
        public int bMaxCount {get; set;}
        // 레벨(업그레이드 레벨)
        public int bLevel {get; set;}
    } 
}
